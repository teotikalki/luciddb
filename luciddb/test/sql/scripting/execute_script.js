importPackage(java.sql)
var conn = DriverManager.getConnection("jdbc:default:connection")
var ps = conn.prepareStatement("create or replace schema boohoo2")
ps.execute()
conn.close()
