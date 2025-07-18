import java.util.Scanner;
public class HelloWorld{
	public static void main(String[] args){
    if(args.length == 0) {
        System.out.println("Please provide one argument");
    }else {
        String arg1 = args[0];
        for(int i = 0; i < arg1.length(); i++){
            char c = arg1.charAt(i);
            if(c == ' ') System.out.println("No whitespace in string");
        }
    }
}