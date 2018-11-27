using IniParser;
using IniParser.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using WindowsInput.Native;

namespace MapeadorDaPortaSerial.Console
{
    public class Configuracoes
    {
        private static IniData _configuracoes;

        public string Porta => _configuracoes["Geral"]["Porta"];

        public bool Debug => Convert.ToBoolean(_configuracoes["Geral"]["Debug"]);

        public Dictionary<string, VirtualKeyCode> MapaDeComandos => CriarMapaDeComandos();

        public Configuracoes(FileIniDataParser fileIniDataParser)
        {
            _configuracoes = fileIniDataParser.ReadFile("Configuracoes.ini");
        }

        private static Dictionary<string, VirtualKeyCode> CriarMapaDeComandos()
        {
            return _configuracoes
                .Sections["Comandos"]
                .ToDictionary(comando => comando.KeyName, comando => ConverterComandoParaTeclaDoTeclado(comando.Value));
        }

        private static VirtualKeyCode ConverterComandoParaTeclaDoTeclado(string tecla)
        {
            return (VirtualKeyCode)Convert.ToInt32(tecla, 16);
        }
    }
}