/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package codegen;
import java.io.*;
import java.security.*;
import javax.crypto.*;
/**
 *
 * @author HP
 */
public class CodeGen {
    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException{
        String password="";
        Scanner scan=new Scanner(System.in);
        System.out.println("Enter the password");
        password=scan.nextLine();
        String salt = generateSalt(); 
        String hashedPassword=hashingFunction(password,salt);
    }
    public static String generateSalt(){
        SecureRandom random=new SecureRandom();
        byte[] salt=new byte[16];
        random.nextBytes(salt);
        String SALT=new String(salt);
        return SALT;
    }
    public static String hashingFunction(String password,String salt) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException{
        MessageDigest md=MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword=md.digest(password.getBytes());
        String HASHEDPASSWORD=new String(hashedPassword);
        return HASHEDPASSWORD;
    }
}