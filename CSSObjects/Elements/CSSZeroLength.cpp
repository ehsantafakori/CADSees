// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- CSSZeroLength.cpp : Implementation of CSSZeroLength
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "CSSZeroLength.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 CSSZeroLength::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	CSSZeroLength, CSSElement,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, CSSZEROLENGTH,
CADSees
|Product Desc:     An OpenSees pre/post-processor
|Company:          Civil Soft Science
|WEB Address:      www.CivilSoftScience.com
)

//-----------------------------------------------------------------------------
CSSZeroLength::CSSZeroLength () : CSSElement () {
	m_type = AcString(_T("zeroLength"));
	pVertList = 0;
}

CSSZeroLength::CSSZeroLength(int tag, int inode, int jnode): CSSElement (tag, "zeroLength")
	, m_iNod(inode)
	, m_jNod(jnode)
{
	pVertList = 0;
	initiatePnts(false);
}

CSSZeroLength::~CSSZeroLength () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus CSSZeroLength::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =CSSElement::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (CSSZeroLength::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	if ( (es =pFiler->writeItem (m_iNod)) != Acad::eOk )
		return (es) ;
	if ( (es =pFiler->writeItem (m_jNod)) != Acad::eOk )
		return (es) ;

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus CSSZeroLength::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =CSSElement::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > CSSZeroLength::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < CSSZeroLength::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	if ( (es =pFiler->readItem (&m_iNod)) != Acad::eOk )
		return (es) ;
	if ( (es =pFiler->readItem (&m_jNod)) != Acad::eOk )
		return (es) ;
	initiatePnts(false);
	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- CSSElement protocols
Adesk::Boolean CSSZeroLength::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;
	mode->geometry().polygon(4, pVertList);
	return (CSSElement::subWorldDraw (mode)) ;
}


Adesk::UInt32 CSSZeroLength::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (CSSElement::subSetAttributes (traits)) ;
}

	//- Osnap points protocol
Acad::ErrorStatus CSSZeroLength::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;
	return (CSSElement::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds)) ;
}

Acad::ErrorStatus CSSZeroLength::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds,
	const AcGeMatrix3d &insertionMat) const
{
	assertReadEnabled () ;
	return (CSSElement::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds, insertionMat)) ;
}

//- Grip points protocol
Acad::ErrorStatus CSSZeroLength::subGetGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
) const {
	assertReadEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)

	return (CSSElement::subGetGripPoints (gripPoints, osnapModes, geomIds)) ;
}

Acad::ErrorStatus CSSZeroLength::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	return (CSSElement::subMoveGripPointsAt (indices, offset)) ;
}

Acad::ErrorStatus CSSZeroLength::subGetGripPoints (
	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
	const AcGeVector3d &curViewDir, const int bitflags
) const {
	assertReadEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return (CSSElement::subGetGripPoints (grips, curViewUnitSize, gripSize, curViewDir, bitflags)) ;
}

Acad::ErrorStatus CSSZeroLength::subMoveGripPointsAt (
	const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
	const int bitflags
) {
	assertWriteEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return (CSSElement::subMoveGripPointsAt (gripAppData, offset, bitflags)) ;
}

void CSSZeroLength::subList() const
{
	CSSElement::subList();
	acutPrintf(_T("\n   iNode:\t%d"), m_iNod);
	acutPrintf(_T("\n   jNode:\t%d"), m_jNod);
}

void CSSZeroLength::updateDeformedGeometry()
{
	assertWriteEnabled(false, true);
	if (!initiatePnts(true))
	{
		m_isNull = true;
	}
}

bool CSSZeroLength::initiatePnts(bool useDeformedGeom)
{
	assertWriteEnabled(false, true);
	AcDbObjectId id;
	if (!ObjUtils::getNode(&id, m_iNod))
	{
		acutPrintf(_T("CSSElement:ERROR finding node object"));
		return false;
	}
	AcDbObject   *pObj = NULL;
	CSSNode *piNode;
	ErrorStatus es = acdbOpenObject(pObj, id, AcDb::kForRead);
    assert(pObj != NULL);
    piNode = CSSNode::cast(pObj);
    assert(piNode != NULL);

	if (!ObjUtils::getNode(&id, m_jNod))
	{
		acutPrintf(_T("CSSElement:ERROR finding node object"));
		piNode->close();
		return false;
	}
	pObj = NULL;
	CSSNode *pjNode;
	es = acdbOpenObject(pObj, id, AcDb::kForRead);
    assert(pObj != NULL);
    pjNode = CSSNode::cast(pObj);
    assert(pjNode != NULL);
	AcGePoint3d crds1, crds2;
	if (useDeformedGeom)
	{
		crds1 = piNode->getDeformedCrds();
		crds2 = pjNode->getDeformedCrds();
	} else
	{
		crds1 = piNode->getCrds();
		crds2 = pjNode->getCrds();
		
	}
	piNode->close();
	pjNode->close();
	AcGeVector3d vec(crds2-crds1);
	if (vec.length() < 1.e-5)
		vec.set(1,0,0);
	double Ln = vec.length()*ZLHTOLRAT;
	AcGeVector3d normal = ObjUtils::getNdm() == 2 ? AcGeVector3d(0, 0, 1) : AcGeVector3d(0, -1, 0);
	normal = -vec.crossProduct(normal);
	normal.normalize();
	int i =  0;
	if (pVertList == 0)
		pVertList = new AcGePoint3d[4];
	pVertList[i++] = crds1;
	crds1 += 0.5*vec + 0.5*Ln*normal;
	pVertList[i++] = crds1;
	crds1 -= normal;
	pVertList[i++] = crds1;
	pVertList[i] = crds2;
	return true;
}
