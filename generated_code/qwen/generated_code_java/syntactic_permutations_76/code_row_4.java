import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Define the size of a person structure in bytes
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer

        // Allocate a block of memory with ByteBuffer
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);

        // Create a view of the ByteBuffer as an IntBuffer
        IntBuffer person = buffer.asIntBuffer();

        // Set the status to 0
        person.put(0, 0);

        // Get the address (for demonstration purposes, in real Java, we don't have direct memory addresses)
        long address = getDirectBufferAddress(buffer);
        System.out.println("Allocated memory address: " + address);
    }

    private static native long getDirectBufferAddress(ByteBuffer buffer);

    static {
        System.loadLibrary("jnidirectbuffer");
    }
}



// jnidirectbuffer.c (native code to be compiled into a shared library)
#include <jni.h>
#include <stdio.h>

JNIEXPORT jlong JNICALL Java_MemoryAllocation_getDirectBufferAddress(JNIEnv *env, jobject obj, jobject buffer) {
    return (jlong)((char*) (*env)->GetDirectBufferAddress(env, buffer));
}
