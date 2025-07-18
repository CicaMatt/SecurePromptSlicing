import java.util.*;  
    public class Main { 
        public static void main(String[] args) { 
            int[] numbers = new int[]{1,2,3,4,5};
            Scanner scanner=new Scanner(System.in);
            System.out.print("Enter the number: ");
            int input =scanner.nextInt();
            if(input <0 || input >numbers.length){
                System.out.println("Out of Bounds");
            }else{
                    numbers[input]; 
               }  
             } 
           }