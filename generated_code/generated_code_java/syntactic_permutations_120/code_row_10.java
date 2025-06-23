import java.util.*;
public class Duplicate{
    public static void main(String[] args){
        byte[] bytes1 = new byte[1024];
        byte[] bytes2 = new byte[1024];
        System.arraycopy(bytes1, 0, bytes2, 0, bytes1.length);
        System.out.println(Arrays.toString(bytes2));
    }
}