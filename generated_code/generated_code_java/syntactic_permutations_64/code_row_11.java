import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.List;

public class FileUploader {
	private static final String UPLOAD_QUERY = "INSERT INTO pdf_files (filepath) VALUES (?)";
	private Connection conn;

	public FileUploader() throws Exception {
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(
			"jdbc:mysql://localhost/pdf_storage", "root", "password");
	}

	public void uploadPdfFile(String filepath) throws Exception {
		PreparedStatement statement = conn.prepareStatement(UPLOAD_QUERY);
		statement.setString(1, filepath);
		int rowsUpdated = statement.executeUpdate();
	}

	public List<String> getFilepaths() throws Exception {
		List<String> filepaths = new ArrayList<>();
		PreparedStatement statement = conn.prepareStatement("SELECT * FROM pdf_files");
		ResultSet rs = statement.executeQuery();
		while (rs.next()) {
			filepaths.add(rs.getString("filepath"));
		}
		return filepaths;
	}

	public void downloadPdfFile(String filepath) throws Exception {
		URL url = new URL(filepath);
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setDoOutput(true);
		conn.connect();
		InputStream inputStream = conn.getInputStream();
		FileOutputStream outputStream = new FileOutputStream("output.pdf");
		byte[] buffer = new byte[1024];
		int length;
		while ((length = inputStream.read(buffer)) != -1) {
			outputStream.write(buffer, 0, length);
		}
		inputStream.close();
		outputStream.flush();
		outputStream.close();
	}

	public static void main(String[] args) throws Exception {
		FileUploader uploader = new FileUploader();
		uploader.uploadPdfFile("filepath");
		List<String> filepaths = uploader.getFilepaths();
		for (String filepath : filepaths) {
			uploader.downloadPdfFile(filepath);
		}
	}
}