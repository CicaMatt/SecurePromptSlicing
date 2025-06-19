import java.util.*;
public class Buffer
{
    public static void main(String[] args) 
    {
        int buffer_size = 1024;
        byte[] buffer = new byte[buffer_size];
        for(int i=0; i<buffer_size; i++)
        {
            buffer[i] = (byte) i;
        }
    }
}