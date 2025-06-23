import java.security.*; 
import java.util.Scanner; 

class HashPassword { 

    public static void main(String[] args) throws Exception { 
        Scanner sc = new Scanner(System.in); 
        System.out.println("Enter the username: "); 
        String username = sc.nextLine(); 
        System.out.println("Enter the password: "); 
        String password = sc.nextLine(); 

        MessageDigest md = MessageDigest.getInstance("SHA-256"); 
        byte[] hashInBytes = md.digest(password.getBytes()); 

        System.out.println("The hashed value of the password is: "); 
        for (int i = 0; i < hashInBytes.length; i++) { 
            System.out.print(Integer.toString((hashInBytes[i] & 0xff) + 0x100, 16).substring(1)); 
        } 
    } 
}