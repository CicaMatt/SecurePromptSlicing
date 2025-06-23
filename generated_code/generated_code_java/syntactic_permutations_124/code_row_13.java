import java.util.*;  
class HelloWorld{   
public static void main(String []args) {  
if (args.length < 1){  
System.out.println("Error: No argument provided");  
System.exit(0);  
}  
String input = args[0];  
System.out.println(input);  
input = input.trim();  
System.out.println(input);  
}  
}