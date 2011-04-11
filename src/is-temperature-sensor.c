/*
 * Copyright (C) 2011 Alex Murray <murray.alex@gmail.com>
 *
 * indicator-sensors is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * indicator-sensors is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with indicator-sensors.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "is-temperature-sensor.h"


G_DEFINE_TYPE(IsTemperatureSensor, is_temperature_sensor, IS_TYPE_SENSOR);

static void is_temperature_sensor_dispose(GObject *object);
static void is_temperature_sensor_finalize(GObject *object);


struct _IsTemperatureSensorPrivate
{
	guint dummy;
};

static void
is_temperature_sensor_class_init(IsTemperatureSensorClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

	g_type_class_add_private(klass, sizeof(IsTemperatureSensorPrivate));

	gobject_class->dispose = is_temperature_sensor_dispose;
	gobject_class->finalize = is_temperature_sensor_finalize;

}

static void
is_temperature_sensor_init(IsTemperatureSensor *self)
{
	IsTemperatureSensorPrivate *priv =
		G_TYPE_INSTANCE_GET_PRIVATE(self, IS_TYPE_TEMPERATURE_SENSOR,
					    IsTemperatureSensorPrivate);

	self->priv = priv;
}



static void
is_temperature_sensor_dispose(GObject *object)
{
	IsTemperatureSensor *self = (IsTemperatureSensor *)object;
	IsTemperatureSensorPrivate *priv = self->priv;

	G_OBJECT_CLASS(is_temperature_sensor_parent_class)->dispose(object);
}

static void
is_temperature_sensor_finalize(GObject *object)
{
	IsTemperatureSensor *self = (IsTemperatureSensor *)object;

	/* Make compiler happy */
	(void)self;

	G_OBJECT_CLASS(is_temperature_sensor_parent_class)->finalize(object);
}

IsSensor *is_temperature_sensor_new(const gchar *family,
				    const gchar *id,
				    const gchar *label)
{
	return is_temperature_sensor_new_full(family, id, label,
					      0.0f, 0.0f);
}

static const gchar *
is_temperature_sensor_units_to_string(IsTemperatureSensorUnits units)
{
	const gchar *string = "";

	switch (units) {
	case IS_TEMPERATURE_SENSOR_UNITS_CELSIUS:
		string = "\302\260C";
		break;
	case IS_TEMPERATURE_SENSOR_UNITS_FARENHEIT:
		string = "\302\260F";
		break;
	case IS_TEMPERATURE_SENSOR_UNITS_KELVIN:
		string = "";
		break;
	default:
		g_warning("Unable to convert IsTemperatureSensorUnits %d to string",
			  units);
	}
	return string;
}

IsSensor *is_temperature_sensor_new_full(const gchar *family,
					 const gchar *id,
					 const gchar *label,
					 gdouble min,
					 gdouble max)
{
	return g_object_new(IS_TYPE_TEMPERATURE_SENSOR,
			    "family", family,
			    "id", id,
			    "label", label,
			    "min", min,
			    "max", max,
			    "units", is_temperature_sensor_units_to_string(IS_TEMPERATURE_SENSOR_UNITS_CELSIUS),
			    NULL);
}

void is_temperature_sensor_set_units(IsTemperatureSensor *sensor,
				     IsTemperatureSensorUnits units)
{
	g_return_if_fail(IS_IS_TEMPERATURE_SENSOR(sensor));

	g_object_set(sensor,
		     "units", is_temperature_sensor_units_to_string(units),
		     NULL);
}

