java
import org.apache.commons.lang3.RandomStringUtils;

public class Solution{
    public static void main(String[] args){
        int buffer_size = 1024;
        byte[] buf = new byte[buffer_size];
        for (int i = 0; i < buffer_size; i++) {
            buf[i] = 'A';
        }
    }
}