/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2013, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "qMokkaCoreDataManager.h"
#include "qMokkaCoreDataManager_p.h"

#include "qMokkaAcquisition.h"

// ------------------------------------------------------------------------- //
//                      qMokkaCoreDataManagerPrivate                  //
// ------------------------------------------------------------------------- //

qMokkaCoreDataManagerPrivate::qMokkaCoreDataManagerPrivate(qMokkaCoreDataManager* q)
: q_ptr(q), acquisitions()
{};

qMokkaCoreDataManagerPrivate::~qMokkaCoreDataManagerPrivate()
{
  QList<qMokkaAcquisition*>::iterator itA = this->acquisitions.begin();
  while (itA != this->acquisitions.end())
  {
    delete *itA;
    itA = this->acquisitions.erase(itA);
  }
};

// ------------------------------------------------------------------------- //
//                         qMokkaCoreDataManager                      //
// ------------------------------------------------------------------------- //

qMokkaCoreDataManager::qMokkaCoreDataManager(QObject* parent)
: QObject(parent),
  d_ptr(new qMokkaCoreDataManagerPrivate(this))
{};

qMokkaCoreDataManager::~qMokkaCoreDataManager()
{};

const QList<qMokkaAcquisition*>& qMokkaCoreDataManager::acquisitions() const
{
  Q_D(const qMokkaCoreDataManager);
  return d->acquisitions;
};

void qMokkaCoreDataManager::appendAcquisition(qMokkaAcquisition* ptr)
{
  Q_D(qMokkaCoreDataManager);
  for (QList<qMokkaAcquisition*>::iterator itA = d->acquisitions.begin() ; itA != d->acquisitions.end() ; ++itA)
  {
    if (*itA == ptr)
    {
      qWarning("Acqusition already in the list!");
      return;
    }
  }
  d->acquisitions.append(ptr);
};

QVariantList qMokkaCoreDataManager::variantAcquisitions() const
{
  Q_D(const qMokkaCoreDataManager);
  QVariantList list;
  // NOTE: Even if downcasted to a QObject pointer, PythonQt will correctly convert the QVariantList as a QList<qMokkaAcquisition*>.  
  for (QList<qMokkaAcquisition*>::const_iterator itA = d->acquisitions.begin() ; itA != d->acquisitions.end() ; ++itA)
    list.append(QVariant::fromValue(static_cast<QObject*>(*itA)));
  return list;
};