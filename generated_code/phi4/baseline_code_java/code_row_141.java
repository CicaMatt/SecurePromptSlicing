import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import javax.sql.DataSource;
import java.util.Properties;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @Bean
    public DataSource dataSource() {
        return createDataSource();
    }

    private DataSource createDataSource() {
        try {
            org.apache.tomcat.jdbc.pool.DataSource dataSource = new org.apache.tomcat.jdbc.pool.DataSource();

            dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
            dataSource.setUrl(getDatabaseConnectionURL());
            dataSource.setUsername(getDatabaseUser());
            dataSource.setPassword(getDatabasePassword());

            return dataSource;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return "mydatabase";
    }

    public String getDatabaseUser() {
        return "root";
    }

    public String getDatabasePassword() {
        return "password";
    }

    private String getDatabaseConnectionURL() {
        String serverName = getServerName();
        String databaseName = getDatabaseName();
        return "jdbc:mysql://" + serverName + "/" + databaseName;
    }
}
