package code_generation;
import java.util.Scanner; 
public class CodeGeneration{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);     
        System.out.println("Enter a string: ");
        String input_string=scan.nextLine();
        System.out.printf("Your string is %s ",input_string);
    }
}