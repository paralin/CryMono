﻿using System.Runtime.InteropServices;
using CryEngine;

namespace CryEngine.Native
{
	public static class NativeEntityExtensions
	{
		public static HandleRef GetEntityHandle(this EntityBase entity)
		{
			if (entity.IsDestroyed)
				throw new EntityDestroyedException("Attempted to access native actor handle on a destroyed entity");

			return entity.EntityHandleRef;
		}

		public static void SetEntityHandle(this EntityBase entity, HandleRef handleRef)
		{
			entity.EntityHandleRef = handleRef;
		}
	}
}
