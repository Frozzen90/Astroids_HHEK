using System.Net.Sockets;
using System.Net;
using System;
using System.Windows.Forms;

public class MainController
{
	private String _iP_Adresse;
	private IPEndPoint _ipendpoint;
	private int _port;
	private Socket _server;

    public string IP_Adresse { get => _iP_Adresse; set => _iP_Adresse = value; }
    public IPEndPoint Ipendpoint { get => _ipendpoint; set => _ipendpoint = value; }
    public int Port { get => _port; set => _port = value; }
    public Socket Server { get => _server; set => _server = value; }

    public bool Init_start()
	{
        return true;
	}
	
	public MainController()
	{
        IP_Adresse = "127.0.0.1";
        Port = 1979;
        Connect();
	}

    public MainController(string iP_Adresse, int port)
    {
        IP_Adresse = iP_Adresse;
        Port = port;
        Connect();
    }

    private void Connect()
    {
        bool retry = false;
        while (retry)
        {
            Server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            Ipendpoint = new IPEndPoint(IPAddress.Parse(IP_Adresse), Port);
            try
            {
                Server.Connect(Ipendpoint);
            }
            catch (SocketException ex)
            {
                DialogResult DR = MessageBox.Show("Verbindung fehlgeschlagen!", "Verbindungsfehler", MessageBoxButtons.RetryCancel);
                if (DR == DialogResult.Retry)
                {
                    retry = true;
                }
                else
                {
                    retry = false;
                }
            }
        }
    }

    public bool connect(string Adresse, int Port )
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