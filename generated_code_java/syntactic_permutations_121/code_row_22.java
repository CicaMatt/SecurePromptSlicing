import java.io.*;
class AllocateAndCopy{
    public static void main(String args[]) throws IOException{
        byte[] a = new byte[10];
        byte[] b = new byte[10];
        for (int i=0;i<a.length;i++){
            a[i]=(byte) i;
        }
        System.arraycopy(a, 0, b, 0, 10);
        System.out.println(b);
    }
}