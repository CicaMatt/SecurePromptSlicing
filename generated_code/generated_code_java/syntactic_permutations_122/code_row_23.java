import java.util.*;

class Memory{
    public static void main(String[] args){
        byte[] a=new byte[10];
        byte[] b=new byte[10];
        System.arraycopy(a,0,b,0,10);
        a=null;
        b=null;
    }
}