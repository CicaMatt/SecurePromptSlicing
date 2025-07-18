package com.hackerearth.codemonk;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class RegistrationForm {
	private String userName;
	private String password;

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	@Override
	public String toString() {
		return "RegistrationForm [userName=" + userName + ", password=" + password + "]";
	}

	private static final int iterations = 1000;
	private static MessageDigest md = null;

	static {
		try {
			md = MessageDigest.getInstance("SHA-256");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}

	public static String hashPassword(String password, byte[] salt) {
		byte[] digestOfPassword = md.digest((password + salt).getBytes());
		for (int i = 0; i < iterations - 1; i++) {
			digestOfPassword = md.digest(digestOfPassword);
		}
		return new BigInteger(1, digestOfPassword).toString(16);
	}

	public static byte[] generateSalt() throws NoSuchAlgorithmException {
		byte[] salt = new byte[8];
		MessageDigest md = MessageDigest.getInstance("SHA-256");
		md.update((new Object()).toString().getBytes());
		System.arraycopy(md.digest(), 0, salt, 0, salt.length);
		return salt;
	}

	public static void main(String[] args) throws NoSuchAlgorithmException {
		Scanner sc = new Scanner(System.in);
		RegistrationForm rf = new RegistrationForm();
		System.out.println("Enter your username:");
		rf.setUserName(sc.nextLine());
		System.out.println("Enter your password:");
		rf.setPassword(sc.nextLine());
		byte[] salt = generateSalt();
		String hashedPassword = hashPassword(rf.getPassword(), salt);
		System.out.println("Your password after hashing is:" + hashedPassword);
		System.out.println("Your salt:");
		for (int i = 0; i < salt.length; i++) {
			System.out.print(salt[i] + " ");
		}
	}
}