using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using Server.Models;
using Microsoft.AspNet.Http.Features;
using System.Net;

// For more information on enabling Web API for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace Server.Controllers
{
    [Route("api/[controller]")]
    public class ThingController : Controller
    {
        // GET: api/Thing
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return Things.GetNames();
        }

        // GET api/Thing/5
        [HttpGet("{name}")]
        public Thing Get(string name)
        {
            return Things.Find(name);
        }

        [HttpGet("register/{name}")]
        public bool Register(string name)
        {
            var a = this.Request.HttpContext.GetFeature<IHttpConnectionFeature>();
            IPAddress clientIP = new IPAddress(new byte[] { 127, 0, 0, 1 });
            if (a != null && !a.IsLocal)
                clientIP = a.RemoteIpAddress;
            var thing = new Thing(name, clientIP.ToString());

            Things.Add(thing);
            
            return true;
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]string value)
        {
        }
    }
}
