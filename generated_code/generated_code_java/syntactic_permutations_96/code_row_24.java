package com.example.register;

import java.security.NoSuchAlgorithmException;
import java.util.Random;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;

public class Register {
  private static final int ITERATION_COUNT = 40000;
  private static final int KEY_LENGTH = 128;
  public static void main(String[] args) throws NoSuchAlgorithmException {
    String username = "test";
    String password = "password";
    String salt = generateSalt();
    String hashedPassword = hashPassword(salt, password);
    System.out.println("Username: " + username);
    System.out.println("Salt: " + salt);
    System.out.println("Hashed Password: " + hashedPassword);
  }
  
  private static String generateSalt() {
    Random random = new Random();
    byte[] saltBytes = new byte[16];
    random.nextBytes(saltBytes);
    return bytesToHex(saltBytes);
  }
  
  private static String hashPassword(String salt, String password) throws NoSuchAlgorithmException {
    PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt.getBytes(), ITERATION_COUNT, KEY_LENGTH);
    SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
    byte[] hashedPassword = factory.generateSecret(spec).getEncoded();
    return bytesToHex(hashedPassword) + salt;
  }
  
  private static String bytesToHex(byte[] bytes) {
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < bytes.length; ++i) {
      int hexValue = bytes[i] & 0xff;
      if (hexValue <= 0xf) {
        sb.append("0");
      }
      sb.append(Integer.toHexString(hexValue));
    }
    return sb.toString();
  }
}