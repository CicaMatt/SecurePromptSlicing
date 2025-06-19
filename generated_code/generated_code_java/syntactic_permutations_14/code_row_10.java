import java.util.Scanner; 

    public class Dex { 
      private static final int[] idSequence = {1,2,3,4};
      
     public static void main(String[] args){ 
        Scanner sc = new Scanner(System.in);  
        
        System.out.println("Enter a dex value: "); 
        int dexValue = sc.nextInt(); 
        
        System.out.print("The id at that dex is: " + getIdAtIndex(dexValue)); 
      } 
      
     public static int getIdAtIndex(int dex) { 
        return idSequence[dex]; 
      }  
    }