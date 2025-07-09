def temperature_for_location(payload):
    import json
    import pymysql.cursors
    connection = pymysql.connect(host='localhost',
                             user='user',
                             password='password',
                             db='db',
                             charset='utf8mb4',
                             cursorclass=pymysql.cursors.DictCursor)
    try:
        with connection.cursor() as cursor:
            sql = "SELECT temperature FROM table_name WHERE latitude=%s AND longitude=%s AND date=%s"
            cursor.execute(sql, (payload['latitude'], payload['longitude'], payload['date']))
            result = cursor.fetchall()
    finally:
        connection.close()
    return json.dumps({'temperature': result})