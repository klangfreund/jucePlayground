/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_ZIPFILE_JUCEHEADER__
#define __JUCE_ZIPFILE_JUCEHEADER__

#include "../files/juce_File.h"
#include "../streams/juce_InputSource.h"
#include "../threads/juce_CriticalSection.h"
#include "../containers/juce_OwnedArray.h"


//==============================================================================
/**
    Decodes a ZIP file from a stream.

    This can enumerate the items in a ZIP file and can create suitable stream objects
    to read each one.
*/
class JUCE_API  ZipFile
{
public:
    /** Creates a ZipFile based for a file. */
    explicit ZipFile (const File& file);

    //==============================================================================
    /** Creates a ZipFile for a given stream.

        @param inputStream                  the stream to read from
        @param deleteStreamWhenDestroyed    if set to true, the object passed-in
                                            will be deleted when this ZipFile object is deleted
    */
    ZipFile (InputStream* inputStream, bool deleteStreamWhenDestroyed);

    /** Creates a ZipFile for a given stream.
        The stream will not be owned or deleted by this class - if you want the ZipFile to
        manage the stream's lifetime, use the other constructor.
    */
    explicit ZipFile (InputStream& inputStream);

    /** Creates a ZipFile for an input source.

        The inputSource object will be owned by the zip file, which will delete
        it later when not needed.
    */
    explicit ZipFile (InputSource* inputSource);

    /** Destructor. */
    ~ZipFile();

    //==============================================================================
    /**
        Contains information about one of the entries in a ZipFile.

        @see ZipFile::getEntry
    */
    struct ZipEntry
    {
        /** The name of the file, which may also include a partial pathname. */
        String filename;

        /** The file's original size. */
        unsigned int uncompressedSize;

        /** The last time the file was modified. */
        Time fileTime;
    };

    //==============================================================================
    /** Returns the number of items in the zip file. */
    int getNumEntries() const noexcept;

    /** Returns a structure that describes one of the entries in the zip file.

        This may return zero if the index is out of range.

        @see ZipFile::ZipEntry
    */
    const ZipEntry* getEntry (int index) const noexcept;

    /** Returns the index of the first entry with a given filename.

        This uses a case-sensitive comparison to look for a filename in the
        list of entries. It might return -1 if no match is found.

        @see ZipFile::ZipEntry
    */
    int getIndexOfFileName (const String& fileName) const noexcept;

    /** Returns a structure that describes one of the entries in the zip file.

        This uses a case-sensitive comparison to look for a filename in the
        list of entries. It might return 0 if no match is found.

        @see ZipFile::ZipEntry
    */
    const ZipEntry* getEntry (const String& fileName) const noexcept;

    /** Sorts the list of entries, based on the filename.
    */
    void sortEntriesByFilename();

    //==============================================================================
    /** Creates a stream that can read from one of the zip file's entries.

        The stream that is returned must be deleted by the caller (and
        zero might be returned if a stream can't be opened for some reason).

        The stream must not be used after the ZipFile object that created
        has been deleted.
    */
    InputStream* createStreamForEntry (int index);

    /** Creates a stream that can read from one of the zip file's entries.

        The stream that is returned must be deleted by the caller (and
        zero might be returned if a stream can't be opened for some reason).

        The stream must not be used after the ZipFile object that created
        has been deleted.
    */
    InputStream* createStreamForEntry (ZipEntry& entry);

    //==============================================================================
    /** Uncompresses all of the files in the zip file.

        This will expand all the entries into a target directory. The relative
        paths of the entries are used.

        @param targetDirectory      the root folder to uncompress to
        @param shouldOverwriteFiles whether to overwrite existing files with similarly-named ones
        @returns success if the file is successfully unzipped
    */
    Result uncompressTo (const File& targetDirectory,
                         bool shouldOverwriteFiles = true);

    /** Uncompresses one of the entries from the zip file.

        This will expand the entry and write it in a target directory. The entry's path is used to
        determine which subfolder of the target should contain the new file.

        @param index                the index of the entry to uncompress - this must be a valid index
                                    between 0 and (getNumEntries() - 1).
        @param targetDirectory      the root folder to uncompress into
        @param shouldOverwriteFiles whether to overwrite existing files with similarly-named ones
        @returns success if all the files are successfully unzipped
    */
    Result uncompressEntry (int index,
                            const File& targetDirectory,
                            bool shouldOverwriteFiles = true);


    //==============================================================================
    /** Used to create a new zip file.

        Create a ZipFile::Builder object, and call its addFile() method to add some files,
        then you can write it to a stream with write().

        Currently this just stores the files with no compression.. That will be added
        soon!
    */
    class Builder
    {
    public:
        Builder();
        ~Builder();

        /** Adds a file while should be added to the archive.
            The file isn't read immediately, all the files will be read later when the writeToStream()
            method is called.

            The compressionLevel can be between 0 (no compression), and 9 (maximum compression).
            If the storedPathName parameter is specified, you can customise the partial pathname that
            will be stored for this file.
        */
        void addFile (const File& fileToAdd, int compressionLevel,
                      const String& storedPathName = String::empty);

        /** Generates the zip file, writing it to the specified stream.
            If the progress parameter is non-null, it will be updated with an approximate
            progress status between 0 and 1.0
        */
        bool writeToStream (OutputStream& target, double* progress) const;

        //==============================================================================
    private:
        class Item;
        friend class OwnedArray<Item>;
        OwnedArray<Item> items;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Builder);
    };

private:
    //==============================================================================
    class ZipInputStream;
    class ZipEntryHolder;
    friend class ZipInputStream;
    friend class ZipEntryHolder;

    OwnedArray <ZipEntryHolder> entries;
    CriticalSection lock;
    InputStream* inputStream;
    ScopedPointer <InputStream> streamToDelete;
    ScopedPointer <InputSource> inputSource;

   #if JUCE_DEBUG
    struct OpenStreamCounter
    {
        OpenStreamCounter() : numOpenStreams (0) {}
        ~OpenStreamCounter();

        int numOpenStreams;
    };

    OpenStreamCounter streamCounter;
   #endif

    void init();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZipFile);
};

#endif   // __JUCE_ZIPFILE_JUCEHEADER__
