#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif



void sleepFor( const uint32_t  aSeconds )
{
#ifdef _WIN32
    Sleep( aSeconds * 1000U );
#else
    sleep( aSeconds );
#endif
}
