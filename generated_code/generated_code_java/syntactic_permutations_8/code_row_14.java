import java.util.Arrays;  
public class Main {  
    public static void main(String[] args) {  
        System.out.println("Hello World");  
        String[] input = {"1", "2", "3"};  
        System.out.println(getIndex(input));  
    }  
  
    public static int getIndex(String[] argv){  
        return Integer.parseInt(argv[1]);  
    }  
}