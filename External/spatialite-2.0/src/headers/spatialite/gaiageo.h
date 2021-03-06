/* 
 gaiageo.h -- Gaia common support for geometries
  
 version 1.0, 2008 May 6

 Author: Sandro Furieri a-furieri@lqt.it

 Copyright (C) 2008  Alessandro Furieri

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 
*/

#ifdef DLL_EXPORT
#define GAIAGEO_DECLARE __declspec(dllexport)
#else
#define GAIAGEO_DECLARE extern
#endif

#ifndef _GAIAGEO_H
#define _GAIAGEO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* constant values for generic geometry classes */
#define GAIA_TYPE_NONE		0
#define GAIA_TYPE_POINT		1
#define GAIA_TYPE_LINESTRING	2
#define GAIA_TYPE_POLYGON	3

/* constants that defines byte storage order  */
#define GAIA_BIG_ENDIAN		0
#define GAIA_LITTLE_ENDIAN	1

/* constants that defines special markers used for encoding of SpatiaLite internal BLOB geometries  */
#define GAIA_MARK_START		0x00
#define GAIA_MARK_END		0xFE
#define GAIA_MARK_MBR		0x7C
#define GAIA_MARK_ENTITY	0x69

/* constants that defines GEOMETRY CLASSes */
#define GAIA_UNKNOWN		0
#define GAIA_POINT		1
#define GAIA_LINESTRING		2
#define GAIA_POLYGON		3
#define GAIA_MULTIPOINT		4
#define GAIA_MULTILINESTRING	5
#define GAIA_MULTIPOLYGON	6
#define GAIA_GEOMETRYCOLLECTION	7

/* constants that defines token codes for WKT parsing */
#define GAIA_COORDINATE		8
#define GAIA_OPENED		9
#define GAIA_CLOSED		10
#define GAIA_COMMA		11
#define GAIA_SPACE		12

/* constants that defines multitype values */
#define GAIA_NULL_VALUE		0
#define GAIA_TEXT_VALUE		1
#define GAIA_INT_VALUE		2
#define GAIA_DOUBLE_VALUE	3

/* constants that defines POINT index for LINESTRING */
#define GAIA_START_POINT	1
#define GAIA_END_POINT		2
#define GAIA_POINTN		3

/* constants that defines MBRs spatial relationships */
#define GAIA_MBR_CONTAINS	1
#define GAIA_MBR_DISJOINT	2
#define GAIA_MBR_EQUAL		3
#define GAIA_MBR_INTERSECTS	4
#define GAIA_MBR_OVERLAPS	5
#define GAIA_MBR_TOUCHES	6
#define GAIA_MBR_WITHIN		7

/* macros */
#define gaiaGetPoint(xy,v,x,y)	{*x = *(xy + (v * 2)); \
				 *y = *(xy + ((v * 2) + 1));}

#define gaiaSetPoint(xy,v,x,y)	{*(xy + (v * 2)) = x; \
				 *(xy + ((v * 2) + 1)) = y;}

    typedef struct gaiaPointStruct
    {
/* an OpenGis POINT */
	double X;		/* X,Y coordinates */
	double Y;
	struct gaiaPointStruct *Next;	/* for double-linked list */
	struct gaiaPointStruct *Prev;	/* for double-linked list */
    } gaiaPoint;
    typedef gaiaPoint *gaiaPointPtr;

    typedef struct gaiaDynamicLineStruct
    {
/* a generic DYNAMIC LINE object */
	gaiaPointPtr First;	/* Points linked list - first */
	gaiaPointPtr Last;	/* Points linked list - last */
    } gaiaDynamicLine;
    typedef gaiaDynamicLine *gaiaDynamicLinePtr;

    typedef struct gaiaLinestringStruct
    {
/* an OpenGis LINESTRING */
	int Points;		/* number of vertices */
	double *Coords;		/* X,Y [vertices] array */
	double MinX;		/* MBR - BBOX */
	double MinY;		/* MBR - BBOX */
	double MaxX;		/* MBR - BBOX */
	double MaxY;		/* MBR - BBOX */
	struct gaiaLinestringStruct *Next;	/* for linked list */
    } gaiaLinestring;
    typedef gaiaLinestring *gaiaLinestringPtr;

    typedef struct gaiaRingStruct
    {
/* a GIS ring - OpenGis LINESTRING, closed */
	int Points;		/* number of vertices */
	double *Coords;		/* X,Y [vertices] array */
	int Clockwise;		/* clockwise / counterclockwise */
	double MinX;		/* MBR - BBOX */
	double MinY;		/* MBR - BBOX */
	double MaxX;		/* MBR - BBOX */
	double MaxY;		/* MBR - BBOX */
	struct gaiaRingStruct *Next;	/* for linked list */
	struct gaiaPolygonStruct *Link;	/* polygon reference */
    } gaiaRing;
    typedef gaiaRing *gaiaRingPtr;

    typedef struct gaiaPolygonStruct
    {
/* an OpenGis POLYGON */
	gaiaRingPtr Exterior;	/* exterior ring */
	int NumInteriors;	/* number of interior rings */
	gaiaRingPtr Interiors;	/* interior rings array */
	int NextInterior;	/* first free interior ring */
	double MinX;		/* MBR - BBOX */
	double MinY;		/* MBR - BBOX */
	double MaxX;		/* MBR - BBOX */
	double MaxY;		/* MBR - BBOX */
	struct gaiaPolygonStruct *Next;	/* for linked list */
    } gaiaPolygon;
    typedef gaiaPolygon *gaiaPolygonPtr;

    typedef struct gaiaGeomCollStruct
    {
/* OpenGis GEOMETRYCOLLECTION */
	int Srid;		/* the SRID value for this GEOMETRY */
	char endian_arch;	/* littleEndian - bigEndian arch for targer CPU */
	char endian;		/* littleEndian - bigEndian */
	const unsigned char *blob;	/* WKB encoded buffer */
	unsigned long size;	/* buffer size */
	unsigned long offset;	/* current offset [for parsing] */
	gaiaPointPtr FirstPoint;	/* Points linked list - first */
	gaiaPointPtr LastPoint;	/* Points linked list - last */
	gaiaLinestringPtr FirstLinestring;	/* Linestrings linked list - first */
	gaiaLinestringPtr LastLinestring;	/* Linestrings linked list - last */
	gaiaPolygonPtr FirstPolygon;	/* Polygons linked list - first */
	gaiaPolygonPtr LastPolygon;	/* Polygons linked list - last */
	double MinX;		/* MBR - BBOX */
	double MinY;		/* MBR - BBOX */
	double MaxX;		/* MBR - BBOX */
	double MaxY;		/* MBR - BBOX */
    } gaiaGeomColl;
    typedef gaiaGeomColl *gaiaGeomCollPtr;

    typedef struct gaiaValueStruct
    {
/* a DBF field multitype value */
	short Type;		/* the type */
	char *TxtValue;		/* the text value */
	int IntValue;		/* the integer value */
	double DblValue;	/* the double value */
    } gaiaValue;
    typedef gaiaValue *gaiaValuePtr;

    typedef struct gaiaDbfFieldStruct
    {
/* a DBF field definition - shapefile attribute */
	char *Name;		/* field name */
	unsigned char Type;	/* field type */
	int Offset;		/* buffer offset [this field begins at *buffer+offset* and extends for *length* bytes */
	unsigned char Length;	/* field total lenght [in bytes] */
	unsigned char Decimals;	/* decimal positions */
	gaiaValuePtr Value;	/* the current multitype value for this attribute */
	struct gaiaDbfFieldStruct *Next;	/* pointer to next element in linked list */
    } gaiaDbfField;
    typedef gaiaDbfField *gaiaDbfFieldPtr;

    typedef struct gaiaDbfListStruct
    {
/* a linked list to containt the DBF fields definitions - shapefile attributes */
	int RowId;		/* the current RowId */
	gaiaGeomCollPtr Geometry;	/* geometry for current entity */
	gaiaDbfFieldPtr First;	/* pointer to first element in linked list */
	gaiaDbfFieldPtr Last;	/* pointer to last element in linker list */
    } gaiaDbfList;
    typedef gaiaDbfList *gaiaDbfListPtr;

    typedef struct gaiaShapefileStruct
    {
/* SHAPEFILE TYPE */
	int endian_arch;
	int Valid;		/* 1 = ready to process */
	int ReadOnly;		/* read or wite mode */
	char *Path;		/* the shapefile abstract path [no suffixes] */
	FILE *flShx;		/* the SHX file handle */
	FILE *flShp;		/* the SHP file handle */
	FILE *flDbf;		/* the DBF file handle */
	int Shape;		/* the SHAPE code for the whole shapefile */
	gaiaDbfListPtr Dbf;	/* the DBF attributes list */
	unsigned char *BufDbf;	/* the DBF I/O buffer */
	int DbfHdsz;		/* the DBF header length */
	int DbfReclen;		/* the DBF record length */
	int DbfSize;		/* current DBF size */
	int DbfRecno;		/* current DBF record number */
	unsigned char *BufShp;	/* the SHP I/O buffer */
	int ShpBfsz;		/* the SHP buffer current size */
	int ShpSize;		/* current SHP size */
	int ShxSize;		/* current SHX size */
	double MinX;		/* the MBR/BBOX for the whole shapefile */
	double MinY;
	double MaxX;
	double MaxY;
	char *LastError;	/* last error message */
    } gaiaShapefile;
    typedef gaiaShapefile *gaiaShapefilePtr;

/* function prototipes */

    GAIAGEO_DECLARE int gaiaEndianArch (void);
    GAIAGEO_DECLARE int gaiaImport16 (const unsigned char *p, int little_endian,
				      int little_endian_arch);
    GAIAGEO_DECLARE int gaiaImport32 (const unsigned char *p, int little_endian,
				      int little_endian_arch);
    GAIAGEO_DECLARE double gaiaImport64 (const unsigned char *p,
					 int little_endian,
					 int little_endian_arch);
    GAIAGEO_DECLARE void gaiaExport16 (unsigned char *p, short value,
				       int little_endian,
				       int little_endian_arch);
    GAIAGEO_DECLARE void gaiaExport32 (unsigned char *p, int value,
				       int little_endian,
				       int little_endian_arch);
    GAIAGEO_DECLARE void gaiaExport64 (unsigned char *p, double value,
				       int little_endian,
				       int little_endian_arch);
    GAIAGEO_DECLARE gaiaPointPtr gaiaAllocPoint (double x, double y);
    GAIAGEO_DECLARE void gaiaFreePoint (gaiaPointPtr ptr);
    GAIAGEO_DECLARE gaiaLinestringPtr gaiaAllocLinestring (int vert);
    GAIAGEO_DECLARE void gaiaFreeLinestring (gaiaLinestringPtr ptr);
    GAIAGEO_DECLARE gaiaRingPtr gaiaAllocRing (int vert);
    GAIAGEO_DECLARE void gaiaFreeRing (gaiaRingPtr ptr);
    GAIAGEO_DECLARE gaiaPolygonPtr gaiaAllocPolygon (int vert, int excl);
    GAIAGEO_DECLARE gaiaPolygonPtr gaiaCreatePolygon (gaiaRingPtr ring);
    GAIAGEO_DECLARE void gaiaFreePolygon (gaiaPolygonPtr p);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaAllocGeomColl (void);
    GAIAGEO_DECLARE void gaiaFreeGeomColl (gaiaGeomCollPtr p);
    GAIAGEO_DECLARE void gaiaAddPointToGeomColl (gaiaGeomCollPtr p, double x,
						 double y);
    GAIAGEO_DECLARE void gaiaMbrLinestring (gaiaLinestringPtr line);
    GAIAGEO_DECLARE void gaiaMbrRing (gaiaRingPtr rng);
    GAIAGEO_DECLARE void gaiaMbrPolygon (gaiaPolygonPtr polyg);
    GAIAGEO_DECLARE void gaiaMbrGeometry (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE gaiaLinestringPtr
	gaiaAddLinestringToGeomColl (gaiaGeomCollPtr p, int vert);
    GAIAGEO_DECLARE void gaiaInsertLinestringInGeomColl (gaiaGeomCollPtr p,
							 gaiaLinestringPtr
							 line);
    GAIAGEO_DECLARE gaiaPolygonPtr gaiaAddPolygonToGeomColl (gaiaGeomCollPtr p,
							     int vert,
							     int interiors);
    GAIAGEO_DECLARE gaiaPolygonPtr gaiaInsertPolygonInGeomColl (gaiaGeomCollPtr
								p,
								gaiaRingPtr
								ring);
    GAIAGEO_DECLARE gaiaRingPtr gaiaAddInteriorRing (gaiaPolygonPtr p, int pos,
						     int vert);
    GAIAGEO_DECLARE void gaiaInsertInteriorRing (gaiaPolygonPtr p,
						 gaiaRingPtr ring);
    GAIAGEO_DECLARE void gaiaAddRingToPolyg (gaiaPolygonPtr polyg,
					     gaiaRingPtr ring);
    GAIAGEO_DECLARE gaiaDynamicLinePtr gaiaAllocDynamicLine (void);
    GAIAGEO_DECLARE void gaiaFreeDynamicLine (gaiaDynamicLinePtr p);
    GAIAGEO_DECLARE gaiaPointPtr
	gaiaAppendPointToDynamicLine (gaiaDynamicLinePtr p, double x, double y);
    GAIAGEO_DECLARE gaiaPointPtr
	gaiaPrependPointToDynamicLine (gaiaDynamicLinePtr p, double x,
				       double y);
    GAIAGEO_DECLARE gaiaPointPtr gaiaDynamicLineInsertAfter (gaiaDynamicLinePtr
							     p, gaiaPointPtr pt,
							     double x,
							     double y);
    GAIAGEO_DECLARE gaiaPointPtr gaiaDynamicLineInsertBefore (gaiaDynamicLinePtr
							      p,
							      gaiaPointPtr pt,
							      double x,
							      double y);
    GAIAGEO_DECLARE void gaiaDynamicLineDeletePoint (gaiaDynamicLinePtr p,
						     gaiaPointPtr pt);
    GAIAGEO_DECLARE gaiaDynamicLinePtr gaiaCloneDynamicLine (gaiaDynamicLinePtr
							     org);
    GAIAGEO_DECLARE gaiaDynamicLinePtr
	gaiaReverseDynamicLine (gaiaDynamicLinePtr org);
    GAIAGEO_DECLARE gaiaDynamicLinePtr
	gaiaDynamicLineSplitBefore (gaiaDynamicLinePtr org, gaiaPointPtr point);
    GAIAGEO_DECLARE gaiaDynamicLinePtr
	gaiaDynamicLineSplitAfter (gaiaDynamicLinePtr org, gaiaPointPtr point);
    GAIAGEO_DECLARE gaiaDynamicLinePtr
	gaiaDynamicLineJoinAfter (gaiaDynamicLinePtr org, gaiaPointPtr point,
				  gaiaDynamicLinePtr toJoin);
    GAIAGEO_DECLARE gaiaDynamicLinePtr
	gaiaDynamicLineJoinBefore (gaiaDynamicLinePtr org, gaiaPointPtr point,
				   gaiaDynamicLinePtr toJoin);
    GAIAGEO_DECLARE gaiaPointPtr gaiaDynamicLineFindByCoords (gaiaDynamicLinePtr
							      p, double x,
							      double y);
    GAIAGEO_DECLARE gaiaPointPtr gaiaDynamicLineFindByPos (gaiaDynamicLinePtr p,
							   int pos);
    GAIAGEO_DECLARE gaiaDynamicLinePtr gaiaCreateDynamicLine (double *coords,
							      int points);
    GAIAGEO_DECLARE double gaiaMeasureLength (double *coords, int vert);
    GAIAGEO_DECLARE double gaiaMeasureArea (gaiaRingPtr ring);
    GAIAGEO_DECLARE void gaiaRingCentroid (gaiaRingPtr ring, double *rx,
					   double *ry);
    GAIAGEO_DECLARE void gaiaClockwise (gaiaRingPtr p);
    GAIAGEO_DECLARE int gaiaIsPointOnRingSurface (gaiaRingPtr ring, double pt_x,
						  double pt_y);
    GAIAGEO_DECLARE double gaiaMinDistance (double x0, double y0,
					    double *coords, int n_vert);
    GAIAGEO_DECLARE int gaiaIsPointOnPolygonSurface (gaiaPolygonPtr polyg,
						     double x, double y);
    GAIAGEO_DECLARE int gaiaIntersect (double *x0, double *y0, double x1,
				       double y1, double x2, double y2,
				       double x3, double y3, double x4,
				       double y4);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaFromSpatiaLiteBlobWkb (const unsigned
							       char *blob,
							       unsigned int
							       size);
    GAIAGEO_DECLARE void gaiaToSpatiaLiteBlobWkb (gaiaGeomCollPtr geom,
						  unsigned char **result,
						  int *size);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaFromSpatiaLiteBlobMbr (const unsigned
							       char *blob,
							       unsigned int
							       size);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaFromWkb (const unsigned char *blob,
						 unsigned int size);
    GAIAGEO_DECLARE void gaiaToWkb (gaiaGeomCollPtr geom,
				    unsigned char **result, int *size);
    GAIAGEO_DECLARE char *gaiaToHexWkb (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE void gaiaFreeValue (gaiaValuePtr p);
    GAIAGEO_DECLARE void gaiaSetNullValue (gaiaDbfFieldPtr field);
    GAIAGEO_DECLARE void gaiaSetIntValue (gaiaDbfFieldPtr field, int value);
    GAIAGEO_DECLARE void gaiaSetDoubleValue (gaiaDbfFieldPtr field,
					     double value);
    GAIAGEO_DECLARE void gaiaSetStrValue (gaiaDbfFieldPtr field, char *str);
    GAIAGEO_DECLARE gaiaDbfFieldPtr gaiaAllocDbfField (char *name,
						       unsigned char type,
						       int offset,
						       unsigned char length,
						       unsigned char decimals);
    GAIAGEO_DECLARE void gaiaFreeDbfField (gaiaDbfFieldPtr p);
    GAIAGEO_DECLARE gaiaDbfListPtr gaiaAllocDbfList (void);
    GAIAGEO_DECLARE void gaiaFreeDbfList (gaiaDbfListPtr list);
    GAIAGEO_DECLARE gaiaDbfFieldPtr gaiaAddDbfField (gaiaDbfListPtr list,
						     char *name,
						     unsigned char type,
						     int offset,
						     unsigned char length,
						     unsigned char decimals);
    GAIAGEO_DECLARE void gaiaResetDbfEntity (gaiaDbfListPtr list);
    GAIAGEO_DECLARE gaiaValuePtr gaiaCloneValue (gaiaValuePtr org);
    GAIAGEO_DECLARE gaiaDbfListPtr gaiaCloneDbfEntity (gaiaDbfListPtr org);
    GAIAGEO_DECLARE gaiaShapefilePtr gaiaAllocShapefile (void);
    GAIAGEO_DECLARE void gaiaFreeShapefile (gaiaShapefilePtr shp);
    GAIAGEO_DECLARE void gaiaOpenShpRead (gaiaShapefilePtr shp,
					  const char *path);
    GAIAGEO_DECLARE void gaiaOpenShpWrite (gaiaShapefilePtr shp,
					   const char *path, int shape,
					   gaiaDbfListPtr list);
    GAIAGEO_DECLARE int gaiaReadShpEntity (gaiaShapefilePtr shp,
					   int current_row);
    GAIAGEO_DECLARE int gaiaWriteShpEntity (gaiaShapefilePtr shp,
					    gaiaDbfListPtr entity);
    GAIAGEO_DECLARE void gaiaFlushShpHeaders (gaiaShapefilePtr shp);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaParseWkt (const unsigned char
						  *dirty_buffer, short type);
    GAIAGEO_DECLARE void gaiaOutWkt (gaiaGeomCollPtr geom, char **result);
    GAIAGEO_DECLARE int gaiaDimension (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE void gaiaGeometryType (gaiaGeomCollPtr geom, char **buf);
    GAIAGEO_DECLARE void gaiaGeometryAliasType (gaiaGeomCollPtr geom,
						char **buf);
    GAIAGEO_DECLARE int gaiaIsEmpty (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE int gaiaMbrsContains (gaiaGeomCollPtr mbr1,
					  gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsDisjoint (gaiaGeomCollPtr mbr1,
					  gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsEqual (gaiaGeomCollPtr mbr1,
				       gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsIntersects (gaiaGeomCollPtr mbr1,
					    gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsOverlaps (gaiaGeomCollPtr mbr1,
					  gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsTouches (gaiaGeomCollPtr mbr1,
					 gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE int gaiaMbrsWithin (gaiaGeomCollPtr mbr1,
					gaiaGeomCollPtr mbr2);
    GAIAGEO_DECLARE void gaiaShiftCoords (gaiaGeomCollPtr geom, double shift_x,
					  double shift_y);
    GAIAGEO_DECLARE void gaiaScaleCoords (gaiaGeomCollPtr geom, double scale_x,
					  double scale_y);
    GAIAGEO_DECLARE void gaiaRotateCoords (gaiaGeomCollPtr geom, double angle);
    GAIAGEO_DECLARE void gaiaReflectCoords (gaiaGeomCollPtr geom, int x_axis,
					    int y_axis);
    GAIAGEO_DECLARE void gaiaSwapCoords (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaCloneGeomColl (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE gaiaLinestringPtr gaiaCloneLinestring (gaiaLinestringPtr
							   line);
    GAIAGEO_DECLARE gaiaRingPtr gaiaCloneRing (gaiaRingPtr ring);
    GAIAGEO_DECLARE gaiaPolygonPtr gaiaClonePolygon (gaiaPolygonPtr polyg);
    GAIAGEO_DECLARE int gaiaLinestringEquals (gaiaLinestringPtr line1,
					      gaiaLinestringPtr line2);
    GAIAGEO_DECLARE int gaiaPolygonEquals (gaiaPolygonPtr geom1,
					   gaiaPolygonPtr geom2);
    GAIAGEO_DECLARE void gaiaBuildMbr (double x1, double y1, double x2,
				       double y2, unsigned char **result,
				       int *size);
    GAIAGEO_DECLARE void gaiaBuildCircleMbr (double x, double y, double radius,
					     unsigned char **result, int *size);
    GAIAGEO_DECLARE int gaiaGetMbrMinX (const unsigned char *blob,
					unsigned int size, double *minx);
    GAIAGEO_DECLARE int gaiaGetMbrMaxX (const unsigned char *blob,
					unsigned int size, double *maxx);
    GAIAGEO_DECLARE int gaiaGetMbrMinY (const unsigned char *blob,
					unsigned int size, double *miny);
    GAIAGEO_DECLARE int gaiaGetMbrMaxY (const unsigned char *blob,
					unsigned int size, double *maxy);

#if OMIT_PROJ == 0		/* including PROJ.4 */

    GAIAGEO_DECLARE double gaiaRadsToDegs (double rads);
    GAIAGEO_DECLARE double gaiaDegsToRads (double degs);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaTransform (gaiaGeomCollPtr org,
						   char *proj_from,
						   char *proj_to);

#endif				/* end including PROJ.4 */

#if OMIT_GEOS == 0		/* including GEOS */

    GAIAGEO_DECLARE int gaiaGeomCollEquals (gaiaGeomCollPtr geom1,
					    gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollDisjoint (gaiaGeomCollPtr geom1,
					      gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollIntersects (gaiaGeomCollPtr geom1,
						gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollOverlaps (gaiaGeomCollPtr geom1,
					      gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollCrosses (gaiaGeomCollPtr geom1,
					     gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollContains (gaiaGeomCollPtr geom1,
					      gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollWithin (gaiaGeomCollPtr geom1,
					    gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollTouches (gaiaGeomCollPtr geom1,
					     gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE int gaiaGeomCollRelate (gaiaGeomCollPtr geom1,
					    gaiaGeomCollPtr geom2,
					    const char *pattern);
    GAIAGEO_DECLARE int gaiaGeomCollDistance (gaiaGeomCollPtr geom1,
					      gaiaGeomCollPtr geom2,
					      double *dist);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeometryIntersection (gaiaGeomCollPtr
							      geom1,
							      gaiaGeomCollPtr
							      geom2);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeometryUnion (gaiaGeomCollPtr geom1,
						       gaiaGeomCollPtr geom2);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeometryDifference (gaiaGeomCollPtr
							    geom1,
							    gaiaGeomCollPtr
							    geom2);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeometrySymDifference (gaiaGeomCollPtr
							       geom1,
							       gaiaGeomCollPtr
							       geom2);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaBoundary (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE int gaiaGeomCollCentroid (gaiaGeomCollPtr geom, double *x,
					      double *y);
    GAIAGEO_DECLARE int gaiaGetPointOnSurface (gaiaGeomCollPtr geom, double *x,
					       double *y);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeomCollSimplify (gaiaGeomCollPtr geom,
							  double tolerance);
    GAIAGEO_DECLARE gaiaGeomCollPtr
	gaiaGeomCollSimplifyPreserveTopology (gaiaGeomCollPtr geom,
					      double tolerance);
    GAIAGEO_DECLARE int gaiaGeomCollLength (gaiaGeomCollPtr geom,
					    double *length);
    GAIAGEO_DECLARE int gaiaGeomCollArea (gaiaGeomCollPtr geom, double *length);
    GAIAGEO_DECLARE int gaiaIsSimple (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE int gaiaIsClosed (gaiaLinestringPtr line);
    GAIAGEO_DECLARE int gaiaIsRing (gaiaLinestringPtr line);
    GAIAGEO_DECLARE int gaiaIsValid (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaConvexHull (gaiaGeomCollPtr geom);
    GAIAGEO_DECLARE gaiaGeomCollPtr gaiaGeomCollBuffer (gaiaGeomCollPtr geom,
							double radius,
							int points);

#endif				/* end including GEOS */

#ifdef __cplusplus
}
#endif

#endif				/* _GAIAGEO_H */
