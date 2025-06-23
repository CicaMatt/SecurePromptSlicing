import java.util.*;
class Solution {  
    public static void main(String[] args) {  
        byte src[] = new byte[10];
        byte dest[] = new byte[10];
        int n = copy("Hello",src,5);
        System.out.print("bytes copied ="+n+"\nsrc = ");
        for(int i=0;i<n;i++)
            System.out.print((char)src[i]);
        System.out.println("\ndest = ");
        for(int i=0;i<n;i++)
            System.out.print((char)dest[i]);
    }
    
    static int copy(String s,byte dest[],int n)  {  
        
        byte src[] = new byte[s.length()];
        for (int i = 0; i < src.length; i++) {
            src[i] = (byte) s.charAt(i);
        }  
        int k=0;
        while(k<n && k<src.length){
            dest[k] = src[k];
            k++;
        }
        return k;
    }
}