package com.snaphunt;
import java.util.*;
import javax.crypto.SecretKeyFactory; 
import javax.crypto.spec.PBEKeySpec; 

public class PasswordHashing{
private static final int iterations = 20*1000;
private static final int saltLen = 32;
private static final int desiredKeyLen = 256;

public String generateSecurePassword(String password){
    byte[] salt = SecureRandom.getInstance("SHA1PRNG").getSeed(saltLen); 
    PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt, iterations, desiredKeyLen);
    SecretKeyFactory skf = null;
    try {
        skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
    } catch (Exception e) {
        e.printStackTrace();
    }
    byte[] hash = skf.generateSecret(spec).getEncoded(); 
    return iterations + ":" + toHex(salt) + ":" + toHex(hash);
}

public static boolean authenticate(String attemptedPassword, String securedPassword){
    String[] parts = securedPassword.split(":");
    int iterations = Integer.parseInt(parts[0]); 
    byte[] salt = fromHex(parts[1]);
    byte[] hash = fromHex(parts[2]);

    PBEKeySpec spec = new PBEKeySpec(attemptedPassword.toCharArray(), salt, iterations, hash.length * 8);
    SecretKeyFactory skf;
    try {
        skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
    } catch (Exception e) {
        e.printStackTrace();
        return false;
    }

    byte[] attemptedHash = skf.generateSecret(spec).getEncoded(); 
    int diff = hash.length ^ attemptedHash.length; 
    for(int i = 0; i < hash.length && i < attemptedHash.length; i++) {
        diff |= hash[i] ^ attemptedHash[i];
    }
    return diff == 0;
}

public static byte[] fromHex(String hex){
    byte[] bytes = new byte[hex.length() / 2]; 
    for(int i = 0; i < bytes.length ;i++) {
        bytes[i] = (byte)Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
    }
    return bytes;
}

public static String toHex(byte[] array){
    BigInteger bi = new BigInteger(1, array); 
    String hex = bi.toString(16);
    int paddingLength = (array.length * 2) - hex.length();
    if(paddingLength > 0) 
        return String.format("%0"  +paddingLength + "d", 0) + hex;
    else
        return hex;
}
}