/**
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *  THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 *  WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 *  MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *  See the Apache Version 2.0 License for specific language governing
 *  permissions and limitations under the License.
 *
 **/

/**
    \file           staticdiskpartitionenumeration.h

    \brief          Enumeration of Static Disk Partition
    \date           09-12-11 14:14:00
    
*/
/*----------------------------------------------------------------------------*/
#ifndef STATICDISKPARTITIONENUMERATION_H
#define STATICDISKPARTITIONENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/diskdepend.h>
#include <scxsystemlib/staticdiskpartitioninstance.h>
#include <scxcorelib/scxlog.h>

namespace SCXSystemLib
{
#if defined(hpux)
    /*----------------------------------------------------------------------------*/
    /**
        Structure contains logical volume and mount point data, if any.
    */
    struct SCXLogicalVolumes
    {
        std::wstring name;     //!< Volume name.
        std::wstring mntDir;   //!< Mount point.
        std::wstring mntType;  //!< Mount point type.
        std::wstring mntOpts;  //!< Mount point options.
    };

    /*----------------------------------------------------------------------------*/
    /**
        Retrieves vector of logical volumes and mount points, if any.

        \param log Handle to a log file.
        \param deps External dependencies.
        \param logVol Return vector to be filled with present logical volumes.
    */
    void GetLogicalVolumes(SCXCoreLib::SCXLogHandle &log, SCXCoreLib::SCXHandle<DiskDepend> &deps,
                            vector<SCXLogicalVolumes> &logVol);
#endif// hpux

    /*----------------------------------------------------------------------------*/
    /**
       Class that represents a collection of Disk Partition data.
    */
    class StaticDiskPartitionEnumeration : public EntityEnumeration<StaticDiskPartitionInstance>
    {
    public:
        static const wchar_t *moduleIdentifier;         //!< Module identifier

        /*----------------------------------------------------------------------------*/
        /**
           Constructor initialized with DiskDependDefault object
        */
        StaticDiskPartitionEnumeration(SCXCoreLib::SCXHandle<DiskDepend> deps);

        /*----------------------------------------------------------------------------*/
        /**
           Virtual destructor
        */
        virtual ~StaticDiskPartitionEnumeration();

        /*----------------------------------------------------------------------------*/
        /**
           Initialize the disk partition instances.
        */
        virtual void Init();

        /*----------------------------------------------------------------------------*/
        /**
            Update the enumeration.

            \param updateInstances If true (default) all instances will be updated.
                              Otherwise only the content of the enumeration will be updated.
 
        */
        virtual void Update(bool updateInstances=true);

        /*----------------------------------------------------------------------------*/
        /**
            Clean up running context.
        */
        virtual void CleanUp();

        /*----------------------------------------------------------------------------*/
        /**
           Dump object as string (for logging).
    
           Parameters:  None
           Retval:      The object represented as a string suitable for logging.
    
        */
        virtual const std::wstring DumpString() const;

    private:
        SCXCoreLib::SCXHandle<DiskDepend> m_deps;       //!< StaticDiskDepend object
        SCXCoreLib::SCXLogHandle m_log;                 //!< Handle to log file 

#if defined(aix)
        /*----------------------------------------------------------------------------*/
        /**
            Processes one disk partition during enumeration.

            \param mountPoints Buffer containing mount points.
            \param mountPointCnt Number of mountpoints in the buffer.
            \param partitionName Partition name.
            \param partitionSize Partition size.
            \param partitionIndex Partition index.
        */
        void ProcessOneDiskPartition(const std::vector<char> &mountPoints, int mountPointCnt, const char* partitionName,
            scxlong partitionSize, unsigned int &partitionIndex);
#endif
#if defined(hpux)
        /*----------------------------------------------------------------------------*/
        /**
            Takes lists of volume groups, logical and physical volumes as generated by "vgdisplay -v" and then
            executes "lvlnboot -v" in order to determine full logical volume name of the boot volume.

            \param logVol List of logical volumes.
            \param logVolShort Returned list of logical volume names in the short form, without path and with leading
                               and trailing spaces removed.
            \param logVolVGIndex Index of a volume group to which particular logical volume belongs to.
            \param physVol List of physical volumes.
            \param physVolVGIndex Index of a volume group to which particular physical volume belongs to.
            \param fullBootLvIndex Returned index of a volume group to which boot logical volume belongs to.
        */
        void GetBootLV(const vector<SCXLogicalVolumes> &logVol, const vector<std::wstring> &logVolShort,
            const vector<size_t> &logVolVGIndex,
            const vector<std::wstring> &physVol, const vector<size_t> &physVolVGIndex, size_t &fullBootLvIndex);

        /*----------------------------------------------------------------------------*/
        /**
            Returns the list of logical volumes found on the system as well as index of the boot logical volume.

            \param logVol Returned list of logical volumes on the system.
            \param bootLvFound Returns true if boot logical volume was successfuly found.
            \param fullBootLvIndex Returned index of a volume group to which boot logical volume belongs to.
        */
        void GetLogicalVolumesBoot(vector<SCXLogicalVolumes> &logVol, bool &bootLvFound, size_t &fullBootLvIndex);
#endif// hpux
    };
}

#endif /* STATICDISKPARTITIONENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
