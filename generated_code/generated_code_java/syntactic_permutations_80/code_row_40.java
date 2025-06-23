import java.util.*;
    
    public class HelloWorld{
        public static void main(String args[]){
            Scanner scanner = new Scanner(System.in);
            String str=scanner.nextLine();
            System.out.println("Entered string is: "+str);
            scanner.close();
        }
    }