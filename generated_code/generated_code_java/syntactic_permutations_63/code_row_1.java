package com.diamonddevgroup.checksum;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class CheckSumCalculator {
	
	private static final int BUFFER_SIZE = 1024 * 1024; // 1 MB

	/**
	 * Reads the contents of a file into a buffer.It then calculates the checksum 
	 * of the buffer.If the checksum is 0 then the buffer is empty.
	 * The number of bytes read and the checksum are saved to another file.
	 */
	public static void main(String[] args) {

		try (FileInputStream inputStream = new FileInputStream(args[0]);
				FileOutputStream outputStream = new FileOutputStream(args[1])) {

			byte[] buffer = new byte[BUFFER_SIZE];
			List<Byte> bytesRead = new ArrayList<>();

			int bytes;
			while ((bytes = inputStream.read(buffer)) != -1) {
				for (int i = 0; i < buffer.length; i++) {
					bytesRead.add((byte) (buffer[i] & 0xFF));
				}
			}

			int checksum = calculateCheckSum(bytesRead);
			if (checksum == 0) {
				System.out.println("Buffer is empty");
			} else {
				System.out.println("Checksum: " + checksum);

				outputStream.write(String.valueOf(bytesRead).getBytes());
				outputStream.write("\n".getBytes());
				outputStream.write(String.valueOf(checksum).getBytes());
			}

		} catch (FileNotFoundException e) {
			System.err.println("File not found");
		} catch (IOException e) {
			System.err.println("Error reading/writing to file");
		}
	}

	/**
	 * Calculates the checksum of a list of bytes.
	 * 
	 * @param bytes
	 *            List of bytes
	 * @return Checksum value as an integer
	 */
	private static int calculateCheckSum(List<Byte> bytes) {
		int checksum = 0;

		for (byte b : bytes) {
			checksum += b;
		}

		return checksum;
	} 
}