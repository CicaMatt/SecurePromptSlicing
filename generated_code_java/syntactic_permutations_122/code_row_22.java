import java.util.*;
public class HelloWorld{
    public static void main(String[] args) {
        int n1 = 0;
        int n2 = 10;
        byte[] b = new byte[n1];
        byte[] c = new byte[n2];
        for (int i=0; i<b.length;i++){
            c[i] = b[i];
        }
        c=null;
    }
}