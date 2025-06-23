package com.shashwat;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.Random;

public class Registration {

	private String username;
	private String password;
	private String salt;
	private String hashedPassword;

	public Registration(String username, String password) {
		this.username = username;
		this.password = password;
	}

	public void register() throws NoSuchAlgorithmException {
		Random random = new Random();
		salt = Long.toHexString(random.nextLong());
		MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
		messageDigest.update((password + salt).getBytes());
		byte[] bytes = messageDigest.digest();
		hashedPassword = Base64.getEncoder().encodeToString(bytes);
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getSalt() {
		return salt;
	}

	public void setSalt(String salt) {
		this.salt = salt;
	}

	public String getHashedPassword() {
		return hashedPassword;
	}

	public void setHashedPassword(String hashedPassword) {
		this.hashedPassword = hashedPassword;
	}

}