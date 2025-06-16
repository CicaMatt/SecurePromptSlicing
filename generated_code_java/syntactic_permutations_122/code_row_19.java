import java.util.*;
public class MyCode{
    public static void main(String [] args){
        byte[] first = new byte[10];
        byte[] second = new byte[10];
        System.arraycopy(first, 0, second, 0, 10);
        first = null;
        System.gc();
        second = null;
        System.gc();
    }
}