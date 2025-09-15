public class PersonMemoryAllocator {

    private static final int PERSON_SIZE = 16; // Assuming sizeof(person) is 16 bytes (4 integers)

    public static native byte[] allocatePerson();

    public static void main(String[] args) {
        byte[] memoryBlock = allocatePerson();
        
        if (memoryBlock != null && memoryBlock.length == PERSON_SIZE) {
            System.out.println("Memory allocated for person: " + memoryBlock.length + " bytes");
        } else {
            System.err.println("Failed to allocate memory for person.");
        }
    }

    static {
        // Load the native library
        System.loadLibrary("PersonAllocator");
    }

    // Native method implementation in C/C++
    /*
    #include <stdlib.h>
    
    extern "C" {
        JNIEXPORT jbyteArray JNICALL Java_PersonMemoryAllocator_allocatePerson(JNIEnv *env, jobject obj) {
            int personSize = 16; // sizeof(person)
            void* memoryBlock = malloc(personSize);
            if (memoryBlock != NULL) {
                return (*env)->NewByteArray(env, personSize);
            }
            return NULL;
        }
    }
    */
}
