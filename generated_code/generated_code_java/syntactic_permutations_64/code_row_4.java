import java.io.*;
import java.sql.*;

public class FileIO {
	
	private String filePath = "C:/uploads/";
	
	public void upload_pdf(String name, byte[] data) throws IOException {
		File f = new File(filePath + name);
		f.createNewFile();
		try (FileOutputStream fos = new FileOutputStream(f)) {
			fos.write(data);
		} catch (IOException e) {
			e.printStackTrace();
		}
		// save filepath to mysql database
		saveFilePathToDatabase(filePath + name, name);
	}
	
	public byte[] download_pdf(String name) throws SQLException {
		ResultSet rs = retrieveFilePathFromDatabase(name);
		if (rs.next()) {
			String filepath = rs.getString("filepath");
			try (FileInputStream fis = new FileInputStream(filepath)) {
				byte[] data = new byte[fis.available()];
				fis.read(data);
				return data;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return null;
	}
	
	public void saveFilePathToDatabase(String filepath, String name) throws SQLException {
		Connection conn = null;
		PreparedStatement stmt = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/fileio", "root", "");
			stmt = conn.prepareStatement("INSERT INTO filepath (filepath, name) VALUES (?, ?)");
			stmt.setString(1, filepath);
			stmt.setString(2, name);
			stmt.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) conn.close();
			if (stmt != null) stmt.close();
		}
	}
	
	public ResultSet retrieveFilePathFromDatabase(String name) throws SQLException {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/fileio", "root", "");
			stmt = conn.prepareStatement("SELECT filepath FROM filepath WHERE name = ?");
			stmt.setString(1, name);
			rs = stmt.executeQuery();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) conn.close();
			if (stmt != null) stmt.close();
		}
		return rs;
	}
}