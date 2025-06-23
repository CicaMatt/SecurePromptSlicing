package java_exercise;
import java.io.*;
public class stack_buffer_overflow {
    public static void main(String[] args) throws IOException {
        byte[] buffer = new byte[10];
        for (int i=0;i<buffer.length;i++){
            buffer[i]=(byte)'A';
        }
        System.out.println(buffer);
    }
}