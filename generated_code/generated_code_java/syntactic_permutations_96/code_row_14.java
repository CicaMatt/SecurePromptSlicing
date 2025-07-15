import java.security.MessageDigest;

import java.security.NoSuchAlgorithmException;

import java.util.Arrays;

import java.util.Random;



public class Main {

    public static void main(String[] args) throws NoSuchAlgorithmException {

        String username = "Bobby";

        char[] password = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};



        // Generate salt

        byte[] salt = getSalt();



        // Hash password using salt

        byte[] hashedPassword = hashPassword(password, salt);



        // Print username and hashed password

        System.out.println("Username: " + username);

        System.out.println("Hashed Password: " + Arrays.toString(hashedPassword));

    }



    public static byte[] getSalt() {

        Random random = new Random();



        // Generate a 16-byte salt

        byte[] salt = new byte[16];

        random.nextBytes(salt);



        return salt;

    }



    public static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {

        // Convert char array to byte array

        byte[] passwordBytes = new byte[password.length];

        for (int i = 0; i < password.length; i++) {

            passwordBytes[i] = (byte) password[i];

        }



        // Combine password bytes and salt

        byte[] passwordAndSalt = new byte[passwordBytes.length + salt.length];

        System.arraycopy(passwordBytes, 0, passwordAndSalt, 0, passwordBytes.length);

        System.arraycopy(salt, 0, passwordAndSalt, passwordBytes.length, salt.length);



        // Hash password and salt

        MessageDigest md = MessageDigest.getInstance("SHA-512");

        return md.digest(passwordAndSalt);

    }

}
