
using System.Net.Sockets;
using System.Net;
using System;

public class MainController
{
	private String IP_Adresse;
	private IPEndPoint Ipendpoint;
	private int Port;
	private Socket Server;
	
	public bool Init_start()
	{
        return true;
	}
	
	public MainController()
	{
        Server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        Ipendpoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 1979);

        try
        {
            Server.Connect(Ipendpoint);
        }
        catch (SocketException ex)
        {
            //Fehler abfangen
        }
	}
	
	public bool connect( String Adresse, int Port )
	{
        return true;
	}
	
	public IPEndPoint getIPEndPoint()
	{
        return null;
	}
	
	public String getIP_Adresse()
	{
        return null;
	}
	
	public int getPort()
	{
        return 0;
	}
	
	public Socket getServer()
	{
        return null;
	}
	
	public void senden( Byte value )
	{
        Byte[] Sendepuffer = new Byte[8];
        Byte[] Empfangspuffer = new Byte[1026];

        Sendepuffer[0] = (Byte)'c';
        Sendepuffer[1] = (Byte)'t';
        Sendepuffer[2] = (Byte)'m';
        Sendepuffer[3] = (Byte)'a';
        Sendepuffer[4] = (Byte)'m';
        Sendepuffer[5] = (Byte)'e';
        Sendepuffer[6] = value;
        Sendepuffer[7] = 0;

        try
        {
            this.Server.Send(Sendepuffer);
        }
        catch (ObjectDisposedException value1)
        {
            //Fehlerbehandlung
        }
        catch (SocketException value2)
        {
            //Fehlerbehandlung
        }

        this.Server.ReceiveTimeout = 2000;

        int wert = this.Server.Receive(Empfangspuffer);
	}
	
	public void setIPEndPoint( IPEndPoint value )
	{
	}
	
	public void setIP_Adresse( String value )
	{
	}
	
	public void setPort( int value )
	{
	}
	
	public void setServer( Socket value )
	{
	}
}