/*
Cuckoo Sandbox - Automated Malware Analysis.
Copyright (C) 2010-2015 Cuckoo Foundation.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MONITOR_NTAPI_H__
#define MONITOR_NTAPI_H__

#define SECURITY_WIN32
#include <stdint.h>
#include <windows.h>
#include <wincrypt.h>
#include <security.h>

typedef LONG NTSTATUS;
typedef void *PIO_APC_ROUTINE;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
    PCHAR  Buffer;
} ANSI_STRING, *PANSI_STRING;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID    Pointer;
    } _;
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef void *HINTERNET;

// evan: already defined in /usr/share/mingw-w64/include/ws2tcpip.h
/*
typedef struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    size_t           ai_addrlen;
    char             *ai_canonname;
    struct sockaddr  *ai_addr;
    struct addrinfo  *ai_next;
} ADDRINFOA, *PADDRINFOA;

typedef struct addrinfoW {
    int               ai_flags;
    int               ai_family;
    int               ai_socktype;
    int               ai_protocol;
    size_t            ai_addrlen;
    PWSTR             ai_canonname;
    struct sockaddr  *ai_addr;
    struct addrinfoW *ai_next;
} ADDRINFOW, *PADDRINFOW;
*/

typedef enum _KEY_INFORMATION_CLASS {
    KeyBasicInformation            = 0,
    KeyNodeInformation             = 1,
    KeyFullInformation             = 2,
    KeyNameInformation             = 3,
    KeyCachedInformation           = 4,
    KeyFlagsInformation            = 5,
    KeyVirtualizationInformation   = 6,
    KeyHandleTagsInformation       = 7,
    MaxKeyInfoClass                = 8
} KEY_INFORMATION_CLASS;

typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation            = 0,
    KeyValueFullInformation             = 1,
    KeyValuePartialInformation          = 2,
    KeyValueFullInformationAlign64      = 3,
    KeyValuePartialInformationAlign64   = 4,
    MaxKeyValueInfoClass                = 5
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_BASIC_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataOffset;
    ULONG DataLength;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_VALUE_ENTRY {
    PUNICODE_STRING    ValueName;
    ULONG        DataLength;
    ULONG        DataOffset;
    ULONG        Type;
} KEY_VALUE_ENTRY, *PKEY_VALUE_ENTRY;

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    void *PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

typedef struct _CLIENT_ID {
    PVOID UniqueProcess;
    PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef ULONG_PTR KAFFINITY;
typedef LONG KPRIORITY;

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    KAFFINITY AffinityMask;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _INITIAL_TEB {
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackCommit;
    PVOID StackCommitMax;
    PVOID StackReserved;
} INITIAL_TEB, *PINITIAL_TEB;

typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation = 1,
    FileFullDirectoryInformation,
    FileBothDirectoryInformation,
    FileBasicInformation,
    FileStandardInformation,
    FileInternalInformation,
    FileEaInformation,
    FileAccessInformation,
    FileNameInformation,
    FileRenameInformation,
    FileLinkInformation,
    FileNamesInformation,
    FileDispositionInformation,
    FilePositionInformation,
    FileFullEaInformation,
    FileModeInformation,
    FileAlignmentInformation,
    FileAllInformation,
    FileAllocationInformation,
    FileEndOfFileInformation,
    FileAlternateNameInformation,
    FileStreamInformation,
    FilePipeInformation,
    FilePipeLocalInformation,
    FilePipeRemoteInformation,
    FileMailslotQueryInformation,
    FileMailslotSetInformation,
    FileCompressionInformation,
    FileObjectIdInformation,
    FileCompletionInformation,
    FileMoveClusterInformation,
    FileQuotaInformation,
    FileReparsePointInformation,
    FileNetworkOpenInformation,
    FileAttributeTagInformation,
    FileTrackingInformation,
    FileIdBothDirectoryInformation,
    FileIdFullDirectoryInformation,
    FileValidDataLengthInformation,
    FileShortNameInformation,
    FileIoCompletionNotificationInformation,
    FileIoStatusBlockRangeInformation,
    FileIoPriorityHintInformation,
    FileSfioReserveInformation,
    FileSfioVolumeInformation,
    FileHardLinkInformation,
    FileProcessIdsUsingFileInformation,
    FileNormalizedNameInformation,
    FileNetworkPhysicalNameInformation,
    FileIdGlobalTxDirectoryInformation,
    FileIsRemoteDeviceInformation,
    FileAttributeCacheInformation,
    FileNumaNodeInformation,
    FileStandardLinkInformation,
    FileRemoteProtocolInformation,
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

#define STATUS_ACCESS_DENIED ((NTSTATUS) 0xc0000022)

typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    ULONG                   MaximumLength;
    ULONG                   Length;
    ULONG                   Flags;
    ULONG                   DebugFlags;
    PVOID                   ConsoleHandle;
    ULONG                   ConsoleFlags;
    HANDLE                  StdInputHandle;
    HANDLE                  StdOutputHandle;
    HANDLE                  StdErrorHandle;
    UNICODE_STRING          CurrentDirectoryPath;
    HANDLE                  CurrentDirectoryHandle;
    UNICODE_STRING          DllPath;
    UNICODE_STRING          ImagePathName;
    UNICODE_STRING          CommandLine;
    PVOID                   Environment;
    ULONG                   StartingPositionLeft;
    ULONG                   StartingPositionTop;
    ULONG                   Width;
    ULONG                   Height;
    ULONG                   CharWidth;
    ULONG                   CharHeight;
    ULONG                   ConsoleTextAttributes;
    ULONG                   WindowFlags;
    ULONG                   ShowWindowFlags;
    UNICODE_STRING          WindowTitle;
    UNICODE_STRING          DesktopName;
    UNICODE_STRING          ShellInfo;
    UNICODE_STRING          RuntimeData;
    RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef void *PPS_CREATE_INFO, *PPS_ATTRIBUTE_LIST;

typedef void *PVOID, **PPVOID;

typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_MODULE {
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID BaseAddress;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    SHORT LoadCount;
    SHORT TlsIndex;
    LIST_ENTRY HashTableEntry;
    ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN Spare;
    HANDLE  Mutant;
    PVOID   ImageBaseAddress;
    PPEB_LDR_DATA LoaderData;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID   SubSystemData;
    PVOID   ProcessHeap;
    PVOID   FastPebLock;
    void   *FastPebLockRoutine;
    void   *FastPebUnlockRoutine;
    ULONG   EnvironmentUpdateCount;
    PPVOID  KernelCallbackTable;
    PVOID   EventLogSection;
    PVOID   EventLog;
    void   *FreeList;
    ULONG   TlsExpansionCounter;
    PVOID   TlsBitmap;
    ULONG   TlsBitmapBits[0x2];
    PVOID   ReadOnlySharedMemoryBase;
    PVOID   ReadOnlySharedMemoryHeap;
    PPVOID  ReadOnlyStaticServerData;
    PVOID   AnsiCodePageData;
    PVOID   OemCodePageData;
    PVOID   UnicodeCaseTableData;
    ULONG   NumberOfProcessors;
    ULONG   NtGlobalFlag;
    BYTE    Spare2[0x4];
    LARGE_INTEGER CriticalSectionTimeout;
    ULONG   HeapSegmentReserve;
    ULONG   HeapSegmentCommit;
    ULONG   HeapDeCommitTotalFreeThreshold;
    ULONG   HeapDeCommitFreeBlockThreshold;
    ULONG   NumberOfHeaps;
    ULONG   MaximumNumberOfHeaps;
    PPVOID *ProcessHeaps;
    PVOID   GdiSharedHandleTable;
    PVOID   ProcessStarterHelper;
    PVOID   GdiDCAttributeList;
    PVOID   LoaderLock;
    ULONG   OSMajorVersion;
    ULONG   OSMinorVersion;
    ULONG   OSBuildNumber;
    ULONG   OSPlatformId;
    ULONG   ImageSubSystem;
    ULONG   ImageSubSystemMajorVersion;
    ULONG   ImageSubSystemMinorVersion;
    ULONG   GdiHandleBuffer[0x22];
    ULONG   PostProcessInitRoutine;
    ULONG   TlsExpansionBitmap;
    BYTE    TlsExpansionBitmapBits[0x80];
    ULONG   SessionId;
} PEB, *PPEB;

#if __x86_64__

#define TLS_TEB 0x30
#define TLS_PEB 0x60

static inline uintptr_t readtls(uint32_t index)
{
    uintptr_t ret;
    __asm__ volatile("movq %%gs:(%1), %0" : "=r" (ret) : "r" (index));
    return ret;
}

static inline void writetls(uint32_t index, uintptr_t value)
{
    __asm__ volatile("movq %0, %%gs:(%1)" :: "r" (value), "r" (index));
}

#else

#define TLS_TEB 0x18
#define TLS_PEB 0x30

static inline uintptr_t readtls(uint32_t index)
{
    uintptr_t ret;
    __asm__ volatile("movl %%fs:(%1), %0" : "=r" (ret) : "r" (index));
    return ret;
}

static inline void writetls(uint32_t index, uintptr_t value)
{
    __asm__ volatile("movl %0, %%fs:(%1)" :: "r" (value), "r" (index));
}

#endif

static inline PEB *get_peb()
{
    return (PEB *) readtls(TLS_PEB);
}

typedef struct _SECTION_IMAGE_INFORMATION {
    PVOID               TransferAddress;
    uint32_t            ZeroBits;
    uint8_t             _PADDING0_[0x4];
    uint64_t            MaximumStackSize;
    uint64_t            CommittedStackSize;
    uint32_t            SubSystemType;
    union {
        struct {
            uint16_t    SubSystemMinorVersion;
            uint16_t    SubSystemMajorVersion;
        } _;
        uint32_t        SubSystemVersion;
    } _;
    uint32_t            GpValue;
    uint16_t            ImageCharacteristics;
    uint16_t            DllCharacteristics;
    uint16_t            Machine;
    uint8_t             ImageContainsCode;
    union {
        uint8_t         ImageFlags;
        struct {
            uint8_t     ComPlusNativeReady : 1;
            uint8_t     ComPlusILOnly : 1;
            uint8_t     ImageDynamicallyRelocated : 1;
            uint8_t     ImageMappedFlat : 1;
            uint8_t     Reserved : 4;
        } _;
    } __;
    uint32_t            LoaderFlags;
    uint32_t            ImageFileSize;
    uint32_t            CheckSum;
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _RTL_USER_PROCESS_INFORMATION {
    ULONG Size;
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef struct _FILE_NAME_INFORMATION {
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

typedef enum  {
    FileFsVolumeInformation       = 1,
    FileFsLabelInformation        = 2,
    FileFsSizeInformation         = 3,
    FileFsDeviceInformation       = 4,
    FileFsAttributeInformation    = 5,
    FileFsControlInformation      = 6,
    FileFsFullSizeInformation     = 7,
    FileFsObjectIdInformation     = 8,
    FileFsDriverPathInformation   = 9,
    FileFsVolumeFlagsInformation  = 10,
    FileFsSectorSizeInformation   = 11
} FS_INFORMATION_CLASS;

typedef struct _FILE_FS_VOLUME_INFORMATION {
    LARGE_INTEGER VolumeCreationTime;
    ULONG         VolumeSerialNumber;
    ULONG         VolumeLabelLength;
    BOOLEAN       SupportsObjects;
    WCHAR         VolumeLabel[1];
} FILE_FS_VOLUME_INFORMATION, *PFILE_FS_VOLUME_INFORMATION;

// evan: already defined in /usr/share/mingw-w64/include/minwinbase.h
/*
typedef enum _FILE_INFO_BY_HANDLE_CLASS {
    FileBasicInfo                   = 0,
    FileStandardInfo                = 1,
    FileNameInfo                    = 2,
    FileRenameInfo                  = 3,
    FileDispositionInfo             = 4,
    FileAllocationInfo              = 5,
    FileEndOfFileInfo               = 6,
    FileStreamInfo                  = 7,
    FileCompressionInfo             = 8,
    FileAttributeTagInfo            = 9,
    FileIdBothDirectoryInfo         = 10,
    FileIdBothDirectoryRestartInfo  = 11,
    FileIoPriorityHintInfo          = 12,
    FileRemoteProtocolInfo          = 13,
    FileFullDirectoryInfo           = 14,
    FileFullDirectoryRestartInfo    = 15,
    FileStorageInfo                 = 16,
    FileAlignmentInfo               = 17,
    FileIdInfo                      = 18,
    FileIdExtdDirectoryInfo         = 19,
    FileIdExtdDirectoryRestartInfo  = 20,
    MaximumFileInfoByHandlesClass
} FILE_INFO_BY_HANDLE_CLASS, *PFILE_INFO_BY_HANDLE_CLASS;
*/

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemProcessorInformation = 1,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemPathInformation = 4,
    SystemProcessInformation = 5,
    SystemCallCountInformation = 6,
    SystemDeviceInformation = 7,
    SystemProcessorPerformanceInformation = 8,
    SystemFlagsInformation = 9,
    SystemCallTimeInformation = 10,
    SystemModuleInformation = 11,
    SystemLocksInformation = 12,
    SystemStackTraceInformation = 13,
    SystemPagedPoolInformation = 14,
    SystemNonPagedPoolInformation = 15,
    SystemHandleInformation = 16,
    SystemObjectInformation = 17,
    SystemPageFileInformation = 18,
    SystemVdmInstemulInformation = 19,
    SystemVdmBopInformation = 20,
    SystemFileCacheInformation = 21,
    SystemPoolTagInformation = 22,
    SystemInterruptInformation = 23,
    SystemDpcBehaviorInformation = 24,
    SystemFullMemoryInformation = 25,
    SystemLoadGdiDriverInformation = 26,
    SystemUnloadGdiDriverInformation = 27,
    SystemTimeAdjustmentInformation = 28,
    SystemSummaryMemoryInformation = 29,
    SystemMirrorMemoryInformation = 30,
    SystemPerformanceTraceInformation = 31,
    SystemObsolete0 = 32,
    SystemExceptionInformation = 33,
    SystemCrashDumpStateInformation = 34,
    SystemKernelDebuggerInformation = 35,
    SystemContextSwitchInformation = 36,
    SystemRegistryQuotaInformation = 37,
    SystemExtendServiceTableInformation = 38,
    SystemPrioritySeperation = 39,
    SystemVerifierAddDriverInformation = 40,
    SystemVerifierRemoveDriverInformation = 41,
    SystemProcessorIdleInformation = 42,
    SystemLegacyDriverInformation = 43,
    SystemCurrentTimeZoneInformation = 44,
    SystemLookasideInformation = 45,
    SystemTimeSlipNotification = 46,
    SystemSessionCreate = 47,
    SystemSessionDetach = 48,
    SystemSessionInformation = 49,
    SystemRangeStartInformation = 50,
    SystemVerifierInformation = 51,
    SystemVerifierThunkExtend = 52,
    SystemSessionProcessInformation = 53,
    SystemLoadGdiDriverInSystemSpace = 54,
    SystemNumaProcessorMap = 55,
    SystemPrefetcherInformation = 56,
    SystemExtendedProcessInformation = 57,
    SystemRecommendedSharedDataAlignment = 58,
    SystemComPlusPackage = 59,
    SystemNumaAvailableMemory = 60,
    SystemProcessorPowerInformation = 61,
    SystemEmulationBasicInformation = 62,
    SystemEmulationProcessorInformation = 63,
    SystemExtendedHandleInformation = 64,
    SystemLostDelayedWriteInformation = 65,
    SystemBigPoolInformation = 66,
    SystemSessionPoolTagInformation = 67,
    SystemSessionMappedViewInformation = 68,
    SystemHotpatchInformation = 69,
    SystemObjectSecurityMode = 70,
    SystemWatchdogTimerHandler = 71,
    SystemWatchdogTimerInformation = 72,
    SystemLogicalProcessorInformation = 73,
    SystemWow64SharedInformationObsolete = 74,
    SystemRegisterFirmwareTableInformationHandler = 75,
    SystemFirmwareTableInformation = 76,
    SystemModuleInformationEx = 77,
    SystemVerifierTriageInformation = 78,
    SystemSuperfetchInformation = 79,
    SystemMemoryListInformation = 80,
    SystemFileCacheInformationEx = 81,
    SystemThreadPriorityClientIdInformation = 82,
    SystemProcessorIdleCycleTimeInformation = 83,
    SystemVerifierCancellationInformation = 84,
    SystemProcessorPowerInformationEx = 85,
    SystemRefTraceInformation = 86,
    SystemSpecialPoolInformation = 87,
    SystemProcessIdInformation = 88,
    SystemErrorPortInformation = 89,
    SystemBootEnvironmentInformation = 90,
    SystemHypervisorInformation = 91,
    SystemVerifierInformationEx = 92,
    SystemTimeZoneInformation = 93,
    SystemImageFileExecutionOptionsInformation = 94,
    SystemCoverageInformation = 95,
    SystemPrefetchPatchInformation = 96,
    SystemVerifierFaultsInformation = 97,
    SystemSystemPartitionInformation = 98,
    SystemSystemDiskInformation = 99,
    SystemProcessorPerformanceDistribution = 100,
    SystemNumaProximityNodeInformation = 101,
    SystemDynamicTimeZoneInformation = 102,
    SystemCodeIntegrityInformation = 103,
    SystemProcessorMicrocodeUpdateInformation = 104,
    SystemProcessorBrandString = 105,
    SystemVirtualAddressInformation = 106,
    SystemLogicalProcessorAndGroupInformation = 107,
    SystemProcessorCycleTimeInformation = 108,
    SystemStoreInformation = 109,
    SystemRegistryAppendString = 110,
    SystemAitSamplingValue = 111,
    SystemVhdBootInformation = 112,
    SystemCpuQuotaInformation = 113,
    SystemNativeBasicInformation = 114,
    SystemErrorPortTimeouts = 115,
    SystemLowPriorityIoInformation = 116,
    SystemBootEntropyInformation = 117,
    SystemVerifierCountersInformation = 118,
    SystemPagedPoolInformationEx = 119,
    SystemSystemPtesInformationEx = 120,
    SystemNodeDistanceInformation = 121,
    SystemAcpiAuditInformation = 122,
    SystemBasicPerformanceInformation = 123,
    SystemQueryPerformanceCounterInformation = 124,
    SystemSessionBigPoolInformation = 125,
    SystemBootGraphicsInformation = 126,
    SystemScrubPhysicalMemoryInformation = 127,
    SystemBadPageInformation = 128,
    SystemProcessorProfileControlArea = 129,
    SystemCombinePhysicalMemoryInformation = 130,
    SystemEntropyInterruptTimingInformation = 131,
    SystemConsoleInformation = 132,
    SystemPlatformBinaryInformation = 133,
    SystemPolicyInformation = 134,
    SystemHypervisorProcessorCountInformation = 135,
    SystemDeviceDataInformation = 136,
    SystemDeviceDataEnumerationInformation = 137,
    SystemMemoryTopologyInformation = 138,
    SystemMemoryChannelInformation = 139,
    SystemBootLogoInformation = 140,
    SystemProcessorPerformanceInformationEx = 141,
    SystemSpare0 = 142,
    SystemSecureBootPolicyInformation = 143,
    SystemPageFileInformationEx = 144,
    SystemSecureBootInformation = 145,
    SystemEntropyInterruptTimingRawInformation = 146,
    SystemPortableWorkspaceEfiLauncherInformation = 147,
    SystemFullProcessInformation = 148,
    SystemKernelDebuggerInformationEx = 149,
    SystemBootMetadataInformation = 150,
    SystemSoftRebootInformation = 151,
    SystemElamCertificateInformation = 152,
    SystemOfflineDumpConfigInformation = 153,
    SystemProcessorFeaturesInformation = 154,
    SystemRegistryReconciliationInformation = 155,
    SystemEdidInformation = 156,
    MaxSystemInfoClass = 157
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _KEY_NAME_INFORMATION {
    ULONG NameLength;
    WCHAR Name[1];
} KEY_NAME_INFORMATION, *PKEY_NAME_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation
} OBJECT_INFORMATION_CLASS;

typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING Name;
    WCHAR NameBuffer[1];
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _FILE_PIPE_INFORMATION {
    ULONG ReadMode;
    ULONG CompletionMode;
} FILE_PIPE_INFORMATION, *PFILE_PIPE_INFORMATION;

typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA {
    ULONG Flags;
    PUNICODE_STRING FullDllName;
    PUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_UNLOADED_NOTIFICATION_DATA, *PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA {
    ULONG Flags;
    PUNICODE_STRING FullDllName;
    PUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_LOADED_NOTIFICATION_DATA, *PLDR_DLL_LOADED_NOTIFICATION_DATA;

typedef union _LDR_DLL_NOTIFICATION_DATA {
    LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
    LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
} LDR_DLL_NOTIFICATION_DATA, *PLDR_DLL_NOTIFICATION_DATA;

typedef VOID (CALLBACK LDR_DLL_NOTIFICATION_FUNCTION)(
    ULONG NotificationReason,
    const LDR_DLL_NOTIFICATION_DATA *NotificationData,
    VOID *Context);

typedef enum _TASKDIALOG_COMMON_BUTTON_FLAGS {
    TDCBF_OK_BUTTON         = 0x0001,
    TDCBF_YES_BUTTON        = 0x0002,
    TDCBF_NO_BUTTON         = 0x0004,
    TDCBF_CANCEL_BUTTON     = 0x0008,
    TDCBF_RETRY_BUTTON      = 0x0010,
    TDCBF_CLOSE_BUTTON      = 0x0020
} TASKDIALOG_COMMON_BUTTON_FLAGS;

typedef enum _SHUTDOWN_ACTION {
    ShutdownNoReboot,
    ShutdownReboot,
    ShutdownPowerOff
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;

static inline UNICODE_STRING *unistr_from_objattr(OBJECT_ATTRIBUTES *obj)
{
    return obj != NULL ? obj->ObjectName : NULL;
}

#define InitializeObjectAttributes(p, n, a, r, s) { \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES); \
    (p)->RootDirectory = r;                  \
    (p)->Attributes = a;                     \
    (p)->ObjectName = n;                     \
    (p)->SecurityDescriptor = s;             \
    (p)->SecurityQualityOfService = NULL;    \
}

#define ProcessBasicInformation 0
#define ThreadBasicInformation 0
#define UNW_FLAG_NHANDLER 0

#define FILE_PIPE_QUEUE_OPERATION           0x00000000
#define FILE_PIPE_COMPLETE_OPERATION        0x00000001

#define FILE_PIPE_BYTE_STREAM_MODE          0x00000000
#define FILE_PIPE_MESSAGE_MODE              0x00000001

#define MAX_PATH_W 0x7fff

#define LDR_DLL_NOTIFICATION_REASON_LOADED 1
#define LDR_DLL_NOTIFICATION_REASON_UNLOADED 2

#define FILE_SUPERSEDED                   0x00000000
#define FILE_OPENED                       0x00000001
#define FILE_CREATED                      0x00000002
#define FILE_OVERWRITTEN                  0x00000003
#define FILE_EXISTS                       0x00000004
#define FILE_DOES_NOT_EXIST               0x00000005

#define MOD_NOREPEAT 0x4000

// evan: already defined in /usr/share/mingw-w64/include/winbase.h
/*
typedef enum _COPYFILE2_MESSAGE_TYPE {
     COPYFILE2_CALLBACK_NONE = 0,
     COPYFILE2_CALLBACK_CHUNK_STARTED,
     COPYFILE2_CALLBACK_CHUNK_FINISHED,
     COPYFILE2_CALLBACK_STREAM_STARTED,
     COPYFILE2_CALLBACK_STREAM_FINISHED,
     COPYFILE2_CALLBACK_POLL_CONTINUE,
     COPYFILE2_CALLBACK_ERROR,
     COPYFILE2_CALLBACK_MAX,
} COPYFILE2_MESSAGE_TYPE;

typedef enum _COPYFILE2_MESSAGE_ACTION {
    COPYFILE2_PROGRESS_CONTINUE = 0,
    COPYFILE2_PROGRESS_CANCEL,
    COPYFILE2_PROGRESS_STOP,
    COPYFILE2_PROGRESS_QUIET,
    COPYFILE2_PROGRESS_PAUSE,
} COPYFILE2_MESSAGE_ACTION;

typedef enum _COPYFILE2_COPY_PHASE {
    COPYFILE2_PHASE_NONE = 0,
    COPYFILE2_PHASE_PREPARE_SOURCE,
    COPYFILE2_PHASE_PREPARE_DEST,
    COPYFILE2_PHASE_READ_SOURCE,
    COPYFILE2_PHASE_WRITE_DESTINATION,
    COPYFILE2_PHASE_SERVER_COPY,
    COPYFILE2_PHASE_NAMEGRAFT_COPY,
    // ... etc phases.
    COPYFILE2_PHASE_MAX,
} COPYFILE2_COPY_PHASE;

#define COPYFILE2_MESSAGE_COPY_OFFLOAD     (0x00000001L)

typedef struct COPYFILE2_MESSAGE {

    COPYFILE2_MESSAGE_TYPE  Type;
    DWORD                   dwPadding;

    union {

        struct {
            DWORD           dwStreamNumber; // monotonically increasing stream number
            DWORD           dwReserved;
            HANDLE           hSourceFile; // handle to the source stream
            HANDLE           hDestinationFile; // handle to the destination stream
            ULARGE_INTEGER  uliChunkNumber; // monotonically increasing chunk number
            ULARGE_INTEGER  uliChunkSize;  // size of the copied chunk
            ULARGE_INTEGER  uliStreamSize; // size of the current stream
            ULARGE_INTEGER  uliTotalFileSize; // size of all streams for this file
        } ChunkStarted;

        struct {
            DWORD           dwStreamNumber; // monotonically increasing stream number
            DWORD           dwFlags;
            HANDLE           hSourceFile; // handle to the source stream
            HANDLE           hDestinationFile; // handle to the destination stream
            ULARGE_INTEGER  uliChunkNumber; // monotonically increasing chunk number
            ULARGE_INTEGER  uliChunkSize;  // size of the copied chunk
            ULARGE_INTEGER  uliStreamSize; // size of the current stream
            ULARGE_INTEGER  uliStreamBytesTransferred; // bytes copied for this stream so far
            ULARGE_INTEGER  uliTotalFileSize; // size of all streams for this file
            ULARGE_INTEGER  uliTotalBytesTransferred; // total bytes copied so far
        } ChunkFinished;

        struct {
            DWORD           dwStreamNumber;
            DWORD           dwReserved;
            HANDLE           hSourceFile; // handle to the source stream
            HANDLE           hDestinationFile; // handle to the destination stream
            ULARGE_INTEGER  uliStreamSize; // size of this stream
            ULARGE_INTEGER  uliTotalFileSize; // total size of all streams for this file
        } StreamStarted;

        struct {
            DWORD           dwStreamNumber;
            DWORD           dwReserved;
            HANDLE           hSourceFile; // handle to the source stream
            HANDLE           hDestinationFile; // handle to the destination stream
            ULARGE_INTEGER  uliStreamSize;
            ULARGE_INTEGER  uliStreamBytesTransferred;
            ULARGE_INTEGER  uliTotalFileSize;
            ULARGE_INTEGER  uliTotalBytesTransferred;
        } StreamFinished;

        struct {
            DWORD           dwReserved;
        } PollContinue;

        struct {
            COPYFILE2_COPY_PHASE    CopyPhase;
            DWORD                   dwStreamNumber;
            HRESULT                 hrFailure;
            DWORD                   dwReserved;
            ULARGE_INTEGER          uliChunkNumber;
            ULARGE_INTEGER          uliStreamSize;
            ULARGE_INTEGER          uliStreamBytesTransferred;
            ULARGE_INTEGER          uliTotalFileSize;
            ULARGE_INTEGER          uliTotalBytesTransferred;
        } Error;

    } Info;

} COPYFILE2_MESSAGE;

typedef
COPYFILE2_MESSAGE_ACTION (CALLBACK *PCOPYFILE2_PROGRESS_ROUTINE)(
  _In_      const COPYFILE2_MESSAGE     *pMessage,
  _In_opt_  PVOID                       pvCallbackContext
);

typedef struct COPYFILE2_EXTENDED_PARAMETERS {
  DWORD                         dwSize;
  DWORD                         dwCopyFlags;
  BOOL                          *pfCancel;
  PCOPYFILE2_PROGRESS_ROUTINE   pProgressRoutine;
  PVOID                         pvCallbackContext;
} COPYFILE2_EXTENDED_PARAMETERS;

typedef struct _CREATEFILE2_EXTENDED_PARAMETERS {
    DWORD dwSize;   
    DWORD dwFileAttributes;
    DWORD dwFileFlags;   
    DWORD dwSecurityQosFlags;	
    LPSECURITY_ATTRIBUTES lpSecurityAttributes; 
    HANDLE hTemplateFile;      
} CREATEFILE2_EXTENDED_PARAMETERS, *PCREATEFILE2_EXTENDED_PARAMETERS, *LPCREATEFILE2_EXTENDED_PARAMETERS;
*/

typedef BOOL (CALLBACK* CALINFO_ENUMPROCEXEX)(LPWSTR, CALID, LPWSTR, LPARAM);

typedef BOOL (CALLBACK* DATEFMT_ENUMPROCEXEX)(LPWSTR, CALID, LPARAM);

typedef BOOL (CALLBACK* TIMEFMT_ENUMPROCEX)(LPWSTR, LPARAM);

typedef BOOL (CALLBACK* LOCALE_ENUMPROCEX)(LPWSTR, DWORD, LPARAM);

// evan: already defined in /usr/share/mingw-w64/include/winnt.h
/*
typedef struct _PROCESSOR_NUMBER {
    WORD   Group;
    BYTE  Number;
    BYTE  Reserved;
} PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;

typedef enum _FILE_ID_TYPE {
      FileIdType,
      ObjectIdType,
      ExtendedFileIdType,
      MaximumFileIdType
} FILE_ID_TYPE, *PFILE_ID_TYPE;

typedef struct FILE_ID_DESCRIPTOR {
    DWORD dwSize;  // Size of the struct
    FILE_ID_TYPE Type; // Describes the type of identifier passed in.
    union {
        LARGE_INTEGER FileId;
        GUID ObjectId;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
        FILE_ID_128 ExtendedFileId;
#endif
    } DUMMYUNIONNAME;
} FILE_ID_DESCRIPTOR, *LPFILE_ID_DESCRIPTOR;

*/

typedef struct _WIN32_MEMORY_RANGE_ENTRY {
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} WIN32_MEMORY_RANGE_ENTRY, *PWIN32_MEMORY_RANGE_ENTRY;

//_Function_class_(BAD_MEMORY_CALLBACK_ROUTINE)
typedef
VOID
WINAPI
BAD_MEMORY_CALLBACK_ROUTINE(
    VOID
    );

typedef BAD_MEMORY_CALLBACK_ROUTINE *PBAD_MEMORY_CALLBACK_ROUTINE;

// evan: below are added to support newly hooked API calls
/*
// ./um/AccCtrl.h
typedef enum _ACCESS_MODE
{
    NOT_USED_ACCESS = 0,
    GRANT_ACCESS,
    SET_ACCESS,
    DENY_ACCESS,
    REVOKE_ACCESS,
    SET_AUDIT_SUCCESS,
    SET_AUDIT_FAILURE
} ACCESS_MODE;

typedef enum _PROGRESS_INVOKE_SETTING {
    ProgressInvokeNever = 1,    // Never invoke the progress function
    ProgressInvokeEveryObject,  // Invoke for each object
    ProgressInvokeOnError,      // Invoke only for each error case
    ProgressCancelOperation,    // Stop propagation and return
    ProgressRetryOperation,     // Retry operation on subtree
#if (NTDDI_VERSION >= NTDDI_VISTA)
    ProgressInvokePrePostError, // Invoke Pre, Post, Error
#endif // (NTDDI_VERSION >= NTDDI_VISTA)
} PROG_INVOKE_SETTING, *PPROG_INVOKE_SETTING;

// ./shared/ws2def.h
typedef struct addrinfoexA
{
    int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
    int                 ai_family;      // PF_xxx
    int                 ai_socktype;    // SOCK_xxx
    int                 ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
    size_t              ai_addrlen;     // Length of ai_addr
    char               *ai_canonname;   // Canonical name for nodename
    struct sockaddr    *ai_addr;        // Binary address
    void               *ai_blob;
    size_t              ai_bloblen;
    LPGUID              ai_provider;
    struct addrinfoexA *ai_next;        // Next structure in linked list
} ADDRINFOEXA, *PADDRINFOEXA, *LPADDRINFOEXA;

typedef struct addrinfoexW
{
    int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
    int                 ai_family;      // PF_xxx
    int                 ai_socktype;    // SOCK_xxx
    int                 ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
    size_t              ai_addrlen;     // Length of ai_addr
    PWSTR               ai_canonname;   // Canonical name for nodename
//  _Field_size_bytes_(ai_addrlen) struct sockaddr    *ai_addr;        // Binary address
    struct sockaddr    *ai_addr;        // Binary address
//  _Field_size_(ai_bloblen) void               *ai_blob;
    void               *ai_blob;
    size_t              ai_bloblen;
    LPGUID              ai_provider;
    struct addrinfoexW *ai_next;        // Next structure in linked list
} ADDRINFOEXW, *PADDRINFOEXW, *LPADDRINFOEXW;

// ./um/AuthZ.h
DECLARE_HANDLE(AUTHZ_ACCESS_CHECK_RESULTS_HANDLE);
DECLARE_HANDLE(AUTHZ_AUDIT_EVENT_HANDLE);
DECLARE_HANDLE(AUTHZ_CAP_CHANGE_SUBSCRIPTION_HANDLE);
DECLARE_HANDLE(AUTHZ_CLIENT_CONTEXT_HANDLE);
DECLARE_HANDLE(AUTHZ_RESOURCE_MANAGER_HANDLE);
DECLARE_HANDLE(AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE);
typedef enum _AUTHZ_CONTEXT_INFORMATION_CLASS
{
    AuthzContextInfoUserSid = 1,
    AuthzContextInfoGroupsSids,
    AuthzContextInfoRestrictedSids,
    AuthzContextInfoPrivileges,
    AuthzContextInfoExpirationTime,
    AuthzContextInfoServerContext,
    AuthzContextInfoIdentifier,
    AuthzContextInfoSource,
    AuthzContextInfoAll,
    AuthzContextInfoAuthenticationId,
    AuthzContextInfoSecurityAttributes,
    AuthzContextInfoDeviceSids,
    AuthzContextInfoUserClaims,
    AuthzContextInfoDeviceClaims,
    AuthzContextInfoAppContainerSid,
    AuthzContextInfoCapabilitySids
} AUTHZ_CONTEXT_INFORMATION_CLASS;

// ./um/avrt.h
typedef enum _AVRT_PRIORITY
{
    AVRT_PRIORITY_VERYLOW = -2,
    AVRT_PRIORITY_LOW,
    AVRT_PRIORITY_NORMAL,
    AVRT_PRIORITY_HIGH,
    AVRT_PRIORITY_CRITICAL
} AVRT_PRIORITY, *PAVRT_PRIORITY;

// ./um/cryptxml.h
typedef enum
{
    //
    // CRYPT_XML_CHARSET_AUTO is supported only in CryptXmlOpenToDecode mode.
    // The encoded XML character set will be determined by the parser from 
    // the XML declaration or the best guess on the characters.
    CRYPT_XML_CHARSET_AUTO        = 0,

    CRYPT_XML_CHARSET_UTF8        = 1,

    CRYPT_XML_CHARSET_UTF16LE     = 2,

    CRYPT_XML_CHARSET_UTF16BE     = 3,
}CRYPT_XML_CHARSET;

typedef struct _CRYPT_XML_BLOB{
    CRYPT_XML_CHARSET                   dwCharset;
//  _Field_range_( 0, CRYPT_XML_BLOB_MAX )
    ULONG                               cbData;    
//  _Field_size_(cbData)
    BYTE                                *pbData;    
}CRYPT_XML_BLOB, *PCRYPT_XML_BLOB;

typedef enum
{
    CRYPT_XML_PROPERTY_MAX_HEAP_SIZE        =   1,  // ULONG, sizeof(ULONG)
    CRYPT_XML_PROPERTY_SIGNATURE_LOCATION   =   2,  // LPCWSTR*, sizeof(LPCWSTR)
    CRYPT_XML_PROPERTY_MAX_SIGNATURES       =   3,  // ULONG, sizeof(ULONG)
    CRYPT_XML_PROPERTY_DOC_DECLARATION      =   4,  // BOOL, sizeof(BOOL)
    CRYPT_XML_PROPERTY_XML_OUTPUT_CHARSET   =   5,  // CRYPT_XML_CHARSET, sizeof(CRYPT_XML_CHARSET)
}CRYPT_XML_PROPERTY_ID;

typedef struct _CRYPT_XML_PROPERTY{
    CRYPT_XML_PROPERTY_ID               dwPropId;
//  _Field_size_bytes_( cbValue )
    const void*                         pvValue;
    ULONG                               cbValue;
}CRYPT_XML_PROPERTY, *PCRYPT_XML_PROPERTY;

typedef
HRESULT
(CALLBACK *PFN_CRYPT_XML_DATA_PROVIDER_READ)(
                    void                *pvCallbackState,
//  _Out_writes_bytes_to_( cbData, *pcbRead )
                    BYTE                *pbData,
                    ULONG               cbData,
//  _Out_range_( 0, cbData )
                    ULONG               *pcbRead
    );

typedef
HRESULT
(CALLBACK *PFN_CRYPT_XML_DATA_PROVIDER_CLOSE)(
                    void                *pvCallbackState
    );

typedef struct _CRYPT_XML_DATA_PROVIDER{
        void                            *pvCallbackState;
        ULONG                           cbBufferSize;
        PFN_CRYPT_XML_DATA_PROVIDER_READ pfnRead;
        PFN_CRYPT_XML_DATA_PROVIDER_CLOSE pfnClose;
}CRYPT_XML_DATA_PROVIDER, *PCRYPT_XML_DATA_PROVIDER;

typedef struct _CRYPT_XML_ALGORITHM{
    ULONG                               cbSize;    
    LPCWSTR                             wszAlgorithm;
    CRYPT_XML_BLOB                      Encoded;
}CRYPT_XML_ALGORITHM, *PCRYPT_XML_ALGORITHM;

typedef
HRESULT
(CALLBACK *PFN_CRYPT_XML_CREATE_TRANSFORM)(
                    const CRYPT_XML_ALGORITHM *pTransform,
                    CRYPT_XML_DATA_PROVIDER *pProviderIn,
                    CRYPT_XML_DATA_PROVIDER *pProviderOut
    );

typedef struct _CRYPT_XML_TRANSFORM_INFO{
    ULONG                               cbSize;    
    LPCWSTR                             wszAlgorithm;
    ULONG                               cbBufferSize;
    DWORD                               dwFlags;
    PFN_CRYPT_XML_CREATE_TRANSFORM      pfnCreateTransform;
}CRYPT_XML_TRANSFORM_INFO, *PCRYPT_XML_TRANSFORM_INFO;

typedef struct _CRYPT_XML_TRANSFORM_CHAIN_CONFIG{
    ULONG                               cbSize;    
    ULONG                               cTransformInfo;
//  _Field_size_(cTransformInfo)
    PCRYPT_XML_TRANSFORM_INFO           *rgpTransformInfo;
} CRYPT_XML_TRANSFORM_CHAIN_CONFIG, *PCRYPT_XML_TRANSFORM_CHAIN_CONFIG;

typedef void*   HCRYPTXML;

// ./um/WinDNS.h
typedef LONG    DNS_STATUS;

typedef
VOID
(WINAPI *DNS_PROXY_COMPLETION_ROUTINE) (
    void *completionContext,
    DNS_STATUS status);

typedef enum DNS_PROXY_INFORMATION_TYPE {
                DNS_PROXY_INFORMATION_DIRECT,
                DNS_PROXY_INFORMATION_DEFAULT_SETTINGS,
                DNS_PROXY_INFORMATION_PROXY_NAME,
                DNS_PROXY_INFORMATION_DOES_NOT_EXIST
}   DNS_PROXY_INFORMATION_TYPE;

typedef struct DNS_PROXY_INFORMATION {
                ULONG version;  // Current version is 1
                DNS_PROXY_INFORMATION_TYPE proxyInformationType;
                PWSTR proxyName;
} DNS_PROXY_INFORMATION;

// ./um/AclAPI.h
typedef void (*FN_PROGRESS) (
    LPWSTR                     pObjectName,    // name of object just processed
    DWORD                      Status,         // status of operation on object
    PPROG_INVOKE_SETTING    pInvokeSetting, // Never, always,
    PVOID                      Args,           // Caller specific data
    BOOL                       SecuritySet     // Whether security was set
);

// ./um/wincrypt.h
typedef void *HCERT_SERVER_OCSP_RESPONSE;
typedef ULONG_PTR HCRYPTPROV_LEGACY;
typedef ULONG_PTR HCRYPTPROV_OR_NCRYPT_KEY_HANDLE;

// ./um/http.h
typedef struct _HTTPAPI_VERSION
{
    USHORT HttpApiMajorVersion;
    USHORT HttpApiMinorVersion;

} HTTPAPI_VERSION, *PHTTPAPI_VERSION;

typedef ULONGLONG      HTTP_OPAQUE_ID,         *PHTTP_OPAQUE_ID;
typedef HTTP_OPAQUE_ID HTTP_REQUEST_ID,        *PHTTP_REQUEST_ID;
typedef HTTP_OPAQUE_ID HTTP_CONNECTION_ID,     *PHTTP_CONNECTION_ID;

typedef enum _HTTP_SERVER_PROPERTY
{
    //
    // Used for enabling server side authentication.
    //

    HttpServerAuthenticationProperty,

    //
    // Used for enabling logging.
    //

    HttpServerLoggingProperty,

    //
    // Used for setting QoS properties.
    //

    HttpServerQosProperty,

    //
    // Used for configuring timeouts.
    //

    HttpServerTimeoutsProperty,

    //
    // Used for limiting request queue lengths.
    //

    HttpServerQueueLengthProperty,

    //
    // Used for manipulating the state.
    //

    HttpServerStateProperty,

    //
    // Used for modifying the verbosity level of 503 type responses
    // generated by server side API.
    //

    HttpServer503VerbosityProperty,

    //
    // Used for manipulating Url Group to Request Queue association.
    //

    HttpServerBindingProperty,

    //
    // Extended authentication property.
    //

    HttpServerExtendedAuthenticationProperty,

    //
    // Listening endpoint property.
    //

    HttpServerListenEndpointProperty,

    //
    // Authentication channel binding property
    //

    HttpServerChannelBindProperty,

    //
    // IP Protection level policy for a Url Group.
    //

    HttpServerProtectionLevelProperty


} HTTP_SERVER_PROPERTY, *PHTTP_SERVER_PROPERTY;

typedef HTTP_OPAQUE_ID HTTP_SERVER_SESSION_ID, *PHTTP_SERVER_SESSION_ID;

typedef enum _HTTP_SERVICE_CONFIG_ID
{
    HttpServiceConfigIPListenList,    // Set, Query & Delete.
    HttpServiceConfigSSLCertInfo,     // Set, Query & Delete.
    HttpServiceConfigUrlAclInfo,      // Set, Query & Delete.
    HttpServiceConfigTimeout,         // Set, Query & Delete.
    HttpServiceConfigCache,           // Set, Query & Delete.

#if _WIN32_WINNT >= _WIN32_WINNT_WIN8

    HttpServiceConfigSslSniCertInfo,  // Set, Query & Delete.
    HttpServiceConfigSslCcsCertInfo,  // Set, Query & Delete.

#endif

    HttpServiceConfigMax

} HTTP_SERVICE_CONFIG_ID, *PHTTP_SERVICE_CONFIG_ID;

typedef ULONGLONG HTTP_URL_CONTEXT;

typedef HTTP_OPAQUE_ID HTTP_URL_GROUP_ID,      *PHTTP_URL_GROUP_ID;

// ./um/WinSock2.h
#define WSAEVENT HANDLE
typedef struct _WSAOVERLAPPED {
    DWORD    Internal;
    DWORD    InternalHigh;
    DWORD    Offset;
    DWORD    OffsetHigh;
    WSAEVENT hEvent;
} WSAOVERLAPPED, FAR * LPWSAOVERLAPPED;

// ./um/WS2tcpip.h
typedef
void
(CALLBACK * LPLOOKUPSERVICE_COMPLETION_ROUTINE)(
    _In_      DWORD    dwError,
    _In_      DWORD    dwBytes,
    _In_      LPWSAOVERLAPPED lpOverlapped
    );
*/

#endif
