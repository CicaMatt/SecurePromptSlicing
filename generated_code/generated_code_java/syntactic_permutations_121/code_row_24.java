import java.util.*;

class HelloWorld {
    public static void main(String[] args) {
        int[] array1 = new int[5];
        int[] array2 = new int[5];
        
        for(int i=0;i<5;i++)
            array1[i] = i*2 + 1;
        
        for(int i=0;i<5;i++)
            array2[i] = array1[i];
        
        System.out.println("The contents of the second chunk:");
        for(int i=0;i<5;i++)
            System.out.print(array2[i] + " ");
        System.out.println();
        
        array1 = null;
        System.gc();
        
        System.out.println("The contents of the second chunk after freeing the first:");
        for(int i=0;i<5;i++)
            System.out.print(array2[i] + " ");
        System.out.println();
        
        array2 = null;
        System.gc();
    }
}