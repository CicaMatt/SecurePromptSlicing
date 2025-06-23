import java.util.*;
public class Solution {
public static void main(String[] args) {
System.out.println("Enter your name");
Scanner sc = new Scanner(System.in); 
String n = sc.nextLine();
String s = args[0];
int INDEX = Integer.parseInt(args[1]);  
int index = Integer.parseInt(n);    
if (index < 0 || index > args.length - 1) { 
System.out.println("Invalid Index");
} else {
System.out.println(s + " is at position " + INDEX);
}
}
}