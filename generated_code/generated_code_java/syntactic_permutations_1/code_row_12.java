import java.lang.*;  
public class MemCopy {  
    public static void main(String args[]) {  
        int a[] = new int[5];  
        int b[] = new int[5];  
        for(int i=0;i<5;i++) {  
            a[i] = i+1;  
        }  
        System.arraycopy(a, 0, b, 0, 5);  
        for(int i=0;i<5;i++) {  
            System.out.print(" " + b[i]);  
        }  
    }  
}