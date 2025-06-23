import java.util.*;

public class AllocateBufferAndOverwriteWithCharacter {
    public static void main(String[] args) { 
        char character = 'A';
        int bufferSize = 1024; // or any size you want
        char[] buffer = new char[buffer_size];
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = character;
        }
    } 
}