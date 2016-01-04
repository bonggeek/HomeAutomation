using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Net;

namespace Server.Models
{
    public class Thing
    {
        public Thing(string name, string ip)
        {
            this.Name = name;
            this.IP = ip;
        }

        public string Name { get; set; }
        public string IP { get; set; }

        public string Get(string propertyName)
        {
            string val = string.Empty;
            this.Properties.TryGetValue(propertyName, out val);
            return val;
        }

        public void Set(string propertyName, string value)
        {
            this.Properties[propertyName] = value;
        }

        public string this[string key]
        {
            get { return this.Properties[key]; }
            set { this.Properties[key] = value; }
        }
        private readonly Dictionary<string, string> Properties = new Dictionary<string, string>();
    }
}
