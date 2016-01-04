using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Server.Models
{
    public class Things
    {
        public static void Add(Thing thing)
        {
            lock (Things.Dictlock)
            {
                Things.thingCollection[thing.Name] = thing;
            }
        }

        public static Thing Find(string name)
        {
            Thing thing = null;
            lock(Things.Dictlock)
            {
                Things.thingCollection.TryGetValue(name, out thing);
            }

            return thing;
        }

        public static IEnumerable<string> GetNames()
        {
            lock(Things.Dictlock)
            {
                return thingCollection.Keys;
            }
        }

        static Dictionary<string, Thing> thingCollection = new Dictionary<string, Thing>();
        static object Dictlock = new object();

        public Things Instance = new Things();
    }
}
