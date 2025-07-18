import java.util.*; 
class Main { 
public static void main(String[] args) { 
System.out.println("Enter a command"); 
Scanner sc = new Scanner(System.in); 
String str = sc.nextLine(); 
Runtime rt = Runtime.getRuntime(); 
try { 
rt.exec(str); 
} 
catch (Exception e) { 
e.printStackTrace(); 
} 
}}