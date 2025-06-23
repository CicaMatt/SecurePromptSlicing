import java.util.*; 
    
      public class HelloWorld {
    
    	private static int[] id_sequence = {1,2,3,4,5};
        public static int findID(int index) {
            return id_sequence[index];
        }
        
        public static void main(String[] args){
            System.out.println("Enter a value between 0 and 4 to get the corresponding ID: ");
            Scanner sc = new Scanner(System.in);
             int index = sc.nextInt();
              if (index < 5 && index >= 0) {
                System.out.println("The ID for this index is " + findID(index));
            } else{
                System.out.println("Invalid Index");
            }
        }
    }