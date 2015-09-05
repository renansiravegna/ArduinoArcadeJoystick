using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using WindowsInput;
using WindowsInput.Native;
using IniParser;

namespace MapeadorDaPortaSerial.Console
{
    class Program
    {
        private static Configuracoes _configuracoes;
        private static SerialPort _serialPort;
        private static InputSimulator _inputSimulator;
        private static Dictionary<string, VirtualKeyCode> _mapaDeComandos;

        static void Main(string[] args)
        {
            var fileIniDataParser = new FileIniDataParser();
            _configuracoes = new Configuracoes(fileIniDataParser);

            _mapaDeComandos = _configuracoes.MapaDeComandos;

            _serialPort = new SerialPort(_configuracoes.Porta, 9600, Parity.None, 8, StopBits.One)
            {
                Handshake = Handshake.None,
                WriteTimeout = 500
            };

            _serialPort.DataReceived += AoReceberMensagem;
            _serialPort.Open();

            _inputSimulator = new InputSimulator();

            while (true) { }
        }

        private static void AoReceberMensagem(object sender, SerialDataReceivedEventArgs e)
		{
		    var mensagemDaPorta = _serialPort.ReadLine().Replace("\r", "");
            var comandosRecebidos = _mapaDeComandos.Where(comando => mensagemDaPorta.Contains(comando.Key)).ToList();

            foreach (var comando in comandosRecebidos)
            {
                if (_configuracoes.Debug)
                    System.Console.WriteLine(mensagemDaPorta + " " + comando);

                var codigoDaTecla = _mapaDeComandos[comando.Key];

                if (mensagemDaPorta.StartsWith("-"))
                    _inputSimulator.Keyboard.KeyUp(codigoDaTecla);
                else
                    _inputSimulator.Keyboard.KeyDown(codigoDaTecla);
            }
        }
    }
}