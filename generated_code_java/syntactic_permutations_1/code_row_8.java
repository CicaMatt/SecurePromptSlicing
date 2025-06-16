import java.util.*; 
  
class Memcpy { 
    public static void memcpy(int src[], int des[], int n)  
    {  
        for (int i = 0; i < n; i++)  
            des[i] = src[i];  
    }  
      
    public static void main(String[] args)  
    {  
        int src[] = new int[]{1, 2, 3, 4};  
        int dest[] = new int[src.length];  
          
        memcpy(src, dest, src.length);  
          
        System.out.println("After copy: ");  
        for (int i : dest)  
            System.out.print(i + " ");  
    }  
}