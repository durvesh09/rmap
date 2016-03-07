# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-02-22 19:13
from __future__ import unicode_literals

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion
import djgeojson.fields
import geoimage.models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='GeorefencedImage',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('active', models.BooleanField(default=True, help_text='Activate this geoimage', verbose_name='Active')),
                ('geom', djgeojson.fields.PointField()),
                ('comment', models.TextField()),
                ('date', models.DateTimeField()),
                ('category', models.CharField(choices=[(b'meteo', b'Meteo phenomena'), (b'others', b'Others')], max_length=50)),
                ('image', geoimage.models.DeletingImageField(upload_to=b'')),
                ('ident', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]