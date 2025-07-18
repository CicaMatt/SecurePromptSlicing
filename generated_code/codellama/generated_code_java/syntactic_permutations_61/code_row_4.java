import java.util.*;
public class test{
    public static void main(String[] args){
        int buffer_size = 500;
        byte[] buffer = new byte[buffer_size];
        for(int i=0;i<10;i++){
            buffer[i] = (byte)(Math.random() * Byte.MAX_VALUE);
            System.out.println("The value of " + i + " is " + buffer[i]);
        }
    }
}