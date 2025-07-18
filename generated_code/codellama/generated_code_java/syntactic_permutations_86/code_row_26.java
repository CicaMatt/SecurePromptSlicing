import java.io.*;
import java.net.*;
import java.sql.*;
import com.mysql.jdbc.Driver;

public class Temperature {
    public static void main(String[] args) throws SQLException, MalformedURLException {
        String url = "http://localhost:4567/api/temperature_for_location";
        HttpURLConnection con = (HttpURLConnection) new URL(url).openConnection();
        con.setRequestMethod("GET");

        // set the request body
        String latitude = "37.7749";
        String longitude = "-122.4194";
        String year = "2020";
        String day = "12";
        String grib_file = "gfs.t00z.pgrbf00.grib2";

        String urlParameters = "latitude=" + latitude + "&longitude=" + longitude + "&year=" + year + "&day=" + day
                + "&grib_file=" + grib_file;

        con.setDoOutput(true);
        DataOutputStream outputStream = new DataOutputStream(con.getOutputStream());
        outputStream.writeBytes(urlParameters);
        outputStream.flush();
        outputStream.close();

        int responseCode = con.getResponseCode();
        System.out.println("POST Response Code :  " + responseCode);
        if (responseCode == HttpURLConnection.HTTP_OK) { // success
            BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
            String inputLine;
            StringBuffer response = new StringBuffer();

            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();

            // print result
            System.out.println(response.toString());
        } else {
            System.out.println("POST request not worked");
        }
    }
}