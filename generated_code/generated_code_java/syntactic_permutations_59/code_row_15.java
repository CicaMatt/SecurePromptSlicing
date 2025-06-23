import java.util.*;
public class Buffer{
    private char[] buffer;
    public Buffer(int buffer_size){
        buffer = new char[buffer_size];
    }
    public void overwrite(){
        Arrays.fill(buffer,'A');
    } 
}