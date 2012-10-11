﻿using System.Reflection;
using System.Runtime.Serialization;
using System.Linq;

namespace CryEngine.Serialization
{
    public class CrySerializationSurrogate : ISerializationSurrogate
    {
        public void GetObjectData(object obj, SerializationInfo info, StreamingContext context)
        {
            // Use default ISerializable behavior, if available
            var serializableObj = obj as ISerializable;
            if (serializableObj != null)
            {
                serializableObj.GetObjectData(info, context);
            }
            else
            {
                // Do our custom serialization here!
                var type = obj.GetType();

                foreach (var fieldInfo in type.GetFields(BindingFlags.Instance | BindingFlags.NonPublic))
                {
                    info.AddValue(fieldInfo.Name, fieldInfo.GetValue(obj));
                }
                

            }
        }

        public object SetObjectData(object obj, SerializationInfo info, StreamingContext context, ISurrogateSelector selector)
        {
            // Is this class ICrySerializable
            var crySerializableObj = obj as ICrySerializable;
            if (crySerializableObj != null)
            {
                return crySerializableObj.SetObjectData(obj, info, context);
            }

            // Do our custom serialization here!
            var type = obj.GetType();
            var typeFields = type.GetFields(BindingFlags.Instance | BindingFlags.NonPublic);
           
            foreach (var fieldInfo in type.GetFields(BindingFlags.Instance | BindingFlags.NonPublic))
            {
                foreach (SerializationEntry entry in info)
                {
                    if (fieldInfo.Name == entry.Name)
                    {
                        fieldInfo.SetValue(obj, entry.Value);
                        break;
                    }
                }
            }

            return obj;
        }

        
    }
}